#shader vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texture;
//layout(location = 1) in vec3 a_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoords;

void main() {
	texCoords = vec2(a_texture.x, 1 - a_texture.y);
	gl_Position = projection * view * model * vec4(a_position, 1.0f);
};

#shader fragment
#version 330 core

in vec2 texCoords;

out vec4 color;

uniform sampler2D u_Texture;

void main() {
	//color = vec4(1.0f, 0.0f, 0.0f, 0.0f);
	//color = vec4(texCoords, 0.0, 0.0);
	color = texture(u_Texture, texCoords);
};
