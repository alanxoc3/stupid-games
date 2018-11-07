// Fragment Shader for Background
#version 150

in vec2 UV;
out vec4 out_color;
uniform sampler2D BkgdTex;

void main() {
	out_color = texture2D(BkgdTex, UV);
}
