#version 150
in vec2 pos;
in vec2 vel;

out vec2 POS;

void main() {
	// Add hs and vs to position, and update friction on hs and vs.
	POS = vec2(pos.x + vel.x, pos.y + vel.y);
}
