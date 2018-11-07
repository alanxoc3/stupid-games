#version 150

flat in uint  Is_Health;

in float Type;
in vec2 TexCoord;
uniform sampler2D Sheet;
uniform int IsHealth;
in vec2 ImgDim;

out vec4 out_color;

void main() {
	if (Type > 0.0f) {
		if (IsHealth == 0) {
			if (ImgDim.x <= 0.0f || ImgDim.y <= 0.0f) {
				out_color = vec4(0.1f, 0.1f, 0.2f, 1.0f);
			} else {
				vec4 tmpTex = texture2D(Sheet, TexCoord);

				if (tmpTex.w > 0.5f)
					out_color = tmpTex;
				else
					discard;
			}
		} else if (IsHealth == 1) { // RED
			out_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
			//out_color = vec4(.9f, .9f, .9f, 1.0f);
		} else if (IsHealth == 2) { // GREEN
			out_color = vec4(.1f, .1f, .1f, 1.0f);
		} } else {
		discard;
	}
}
