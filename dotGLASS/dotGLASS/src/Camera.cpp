#include "Camera.h"

void dotGLASS::Camera::processKeyboard(dotGLASS::CameraMovement direction, float deltaTime) {
	float velocity = this->movementSpeed * deltaTime;
	if (direction == FORWARD) {
		this->position += this->front * velocity;
	}
	if (direction == BACKWARD) {
		this->position -= this->front * velocity;
	}
	if (direction == RIGHT) {
		this->position += this->right * velocity;
	}
	if (direction == LEFT) {
		this->position -= this->right * velocity;
	}
}

void dotGLASS::Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
	xOffset *= this->mouseSensitivity;
	yOffset *= this->mouseSensitivity;

	this->yaw += xOffset;
	this->pitch += yOffset;

	if (constrainPitch) {
		if (this->pitch > 89.0f) {
			this->pitch = 89.0f;
		}
		if (this->pitch < -89.0f) {
			this->pitch = -89.0f;
		}
	}

	updateCameraVectors();
}

void dotGLASS::Camera::processMouseScroll(float yOffset) {}

void dotGLASS::Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}
