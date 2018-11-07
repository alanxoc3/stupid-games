#version 150

in vec2 pos;
uniform mat4 proj;

void main() {
	gl_Position =  proj * vec4(pos, -1.0f, 1.0f);
}
