#version 150

in vec2 pos;
uniform mat4 proj;
uniform vec2 mpos;

void main() {
	vec2 tmpPos = pos + mpos;
	//vec2 tmpPos = vec2(3.0f, 10.0f);
	gl_Position =  proj * vec4(tmpPos, -1.0f, 1.0f);
}
