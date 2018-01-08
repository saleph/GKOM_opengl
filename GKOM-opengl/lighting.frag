#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
uniform vec3 objectColor;
uniform vec3 lightColor;
//in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);  
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);
	//FragColor = vec4(lightColor * objectColor, 1.0);
}