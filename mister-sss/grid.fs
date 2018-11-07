#version 150

out vec4 out_color;

uniform sampler2D texFrame;
uniform vec2 screen;

void main() {
	vec4 tmpCol = texture(texFrame, vec2(gl_FragCoord.x / screen.x, gl_FragCoord.y / screen.y));
	tmpCol = vec4(1.0f, 1.0f, 1.0f, 1.0f) - tmpCol;
	out_color = vec4(tmpCol.x, tmpCol.y, tmpCol.z, 1.0f);
	
	//out_color = vec4(0.2f, 0.4f, 0.7f, 1.0f) * gl_FragCoord;
}
