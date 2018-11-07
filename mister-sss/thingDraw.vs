#version 150

in float type;
in vec3  pos;
in vec2  dim;
in vec2  img_ctr;
in vec2  img_dim;
in vec2  img_off;
in float hp;
in float max_hp;

out float TYPE;
out vec2  DIM;
out vec2  IMG_CTR;
out vec2  IMG_DIM;
out vec2  IMG_OFF;
out float HP;
out float MAX_HP;

void main() {
	TYPE = type;
	DIM = dim;
	IMG_CTR = img_ctr;
	IMG_DIM = img_dim;
	IMG_OFF = img_off;
	HP = hp;
	MAX_HP = max_hp;

	gl_Position = vec4(pos.xyz, 1.0f);
}
