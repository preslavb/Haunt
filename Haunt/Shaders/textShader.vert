#version 130

in vec4 vertexColor;

out vec4 fragmentColor;

uniform vec4 tint;

void main() {
	fragmentColor = vec4(1, 1, 1, 1) * tint;
}