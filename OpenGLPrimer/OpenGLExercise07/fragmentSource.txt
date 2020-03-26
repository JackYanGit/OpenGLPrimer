#version 330 core							   
in vec4 vertexColor;
in vec2 TextCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourFace; 					   
out vec4 FragColor;	
void main()								   
{			
	FragColor = mix(texture(ourTexture,TextCoord),texture(ourFace,TextCoord),0.2);
	//FragColor = texture(ourTexture,TextCoord)*texture(ourFace,TextCoord);
}											   