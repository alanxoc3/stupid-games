#version 150

// texture coords
in vec2 pos;
in vec2 tex;

out vec2 TEX;

void main() {
	TEX = tex;
	gl_Position = vec4(pos, 0.0f, 1.0f);
}
