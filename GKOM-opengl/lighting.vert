#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//layout (location = 1) in vec3 aColor;
//layout (location = 1) in vec2 aTexCoord;

out vec3 ourColor;
//out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = vec3(0.7,0.2,0.6);
    //TexCoord = aTexCoord;
}
