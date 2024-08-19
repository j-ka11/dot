#include "Engine.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);

dotGLASS::Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = 400.0f;
float lastY = 400.0f;
bool keys[1024];
bool firstMouse = true;

float lastFrame = 0.0f;
float deltaTime = 0.0f;

dotGLASS::Engine::Engine() {}

dotGLASS::Engine::~Engine() {}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
	}
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.processMouseMovement(xOffset, yOffset);
}

void dotGLASS::Engine::doMovement() {
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
		camera.processKeyboard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
		camera.processKeyboard(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
		camera.processKeyboard(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
		camera.processKeyboard(RIGHT, deltaTime);
	}
}

void dotGLASS::Engine::openWindow() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//window = glfwCreateWindow(1600, 1200, "dotGLASS", nullptr, nullptr); // Windowed
	window = glfwCreateWindow(800, 600, "dotGLASS", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();
}

void dotGLASS::Engine::run() {
	glfwInit();
	openWindow();

	//enabling blending
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GLCall(glEnable(GL_DEPTH_TEST));

	//creating an extra scope to handle openGL not terminating
	{
		dotGLASS::Object::Lamp* lamp = new dotGLASS::Object::Lamp();

		int screenWidth, screenHeight;
		glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

		std::string modelShaderFile = "dotGLASS/res/shaders/modelLoading.shader";
		Shader modelShader(modelShaderFile);
		modelShader.unBind();

		dotGLASS::Object::ArObject* nano = new dotGLASS::Object::Nanosuit();

		std::string lampShaderFile = "dotGLASS/res/shaders/lamp.shader";
		Shader lampShader(lampShaderFile);
		lampShader.unBind();

		glm::mat4 projection = glm::perspective(camera.getZoom(), 1600.0f / 1200.0f, 0.1f, 100.f);

		glm::vec3 lightPosition = lamp->getLightPosition();

		while (!glfwWindowShouldClose(window)) {
			//render here
			GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			//poll for and process events
			glfwPollEvents();
			doMovement();

			glm::mat4 view = camera.getViewMatrix();

			//render arrow
			modelShader.bind();

			//modelShader.setUniform1i("texture_diffuse", 0);

			modelShader.setUniform3f("objectColor", 0.25, 0.745f, 0.829f);
			modelShader.setUniform3f("lightColor", 1.0f, 0.5f, 1.0f);
			modelShader.setUniform3f("lightPos", lightPosition.x, lightPosition.y, lightPosition.z);
			modelShader.setUniform3f("viewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
			model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));

			modelShader.setUniformMat4("projection", projection);
			modelShader.setUniformMat4("view", view);
			modelShader.setUniformMat4("model", model);

			nano->draw();

			modelShader.unBind();

			//render light
			lampShader.bind();

			model = glm::translate(glm::mat4(1.0f), lightPosition);
			model = glm::scale(model, glm::vec3(0.2f));

			lampShader.setUniformMat4("projection", projection);
			lampShader.setUniformMat4("view", view);
			lampShader.setUniformMat4("model", model);

			lamp->bind();
			lamp->draw();

			lampShader.unBind();

			//swap front and back buffers
			glfwSwapBuffers(window);

			//Uncomment this if using full screen
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);
		}
		delete lamp;
		delete nano;
	}

	glfwTerminate();
}
