#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec3 Normal;  
in vec3 FragPos; 
uniform vec3 objectColor;
uniform vec3 lightColor;
//in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 lightPos;  

void main() {
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);  

	// ambient color
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	// diffuse component
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
	//FragColor = vec4(lightColor * objectColor, 1.0);
}