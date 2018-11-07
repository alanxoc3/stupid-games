// Vertex Shader for Background
#version 150

uniform vec2 rep_num;
uniform vec2 img_dim;
in vec2 pos;
in vec2 uv;
uniform vec2 view;

out vec2 UV;

void main() {
	vec2 tmpVec = vec2(view.x / img_dim.x, -view.y / img_dim.y);
	UV = uv * rep_num + tmpVec;
	gl_Position = vec4(pos, 0.0f, 1.0f);
}
