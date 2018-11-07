#version 150

// texture coords
in vec2 TEX; 
out vec4 outColor;

uniform sampler2D fbTex;

void main() {
	outColor = texture(fbTex, TEX);
}
