#version 330 core
out vec4 FragColor;

uniform float uniColor;

void main() {
	FragColor = vec4(0.2, uniColor, 0.3, 1.0); 
}