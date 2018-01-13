#version 330 core
out vec4 FragColor;
  
in vec3 Normal;  
in vec3 FragPos; 
in vec2 TexCoord;

uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 lightPos;  

uniform sampler2D ourTexture;

void main() {
    vec4 textColor = texture(ourTexture, TexCoord);  

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	
	// ambient component
	float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

	// diffuse component
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// spectacular
	float specularStrength = 0.99;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	// combine
    vec3 result = (ambient + diffuse + specular) * textColor.xyz;
    FragColor = vec4(result, 1.0);
}