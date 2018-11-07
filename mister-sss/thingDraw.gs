#version 150

layout(points) in;
layout(triangle_strip, max_vertices = 6) out;

uniform mat4 proj;
uniform mat4 view;
uniform vec2 SHEET_DIM;
uniform int IsHealth;
uniform float green_z;
uniform float red_z;

in float TYPE[];
in vec2  DIM[]; in vec2  IMG_CTR[];
in vec2  IMG_DIM[];
in vec2  IMG_OFF[];
in float HP[];
in float MAX_HP[];

out vec2  ImgDim;
out float Type;
out vec2 TexCoord;

void main() {
	if (TYPE[0] > 0.0f) {
	// STEP 1: SET UP VARIABLES
		vec4 tmpPos = gl_in[0].gl_Position + vec4(IMG_CTR[0], 0.0f, 0.0f);
		vec2 tmpDim = IMG_DIM[0];

		if (tmpDim.x <= 0.0f || tmpDim.y <= 0.0f) {
			tmpPos = gl_in[0].gl_Position;
			tmpDim = DIM[0];
		}

		ImgDim = IMG_DIM[0];
		Type = TYPE[0];

		vec4 bottomLeft  = proj * view * (vec4(tmpPos.xyz, 1.0f));
		vec4 bottomRight = proj * view * (tmpPos + vec4(tmpDim.x, 0.0f,     0.0f, 0.0f));
		vec4 topRight    = proj * view * (tmpPos + vec4(tmpDim.x, tmpDim.y, 0.0f, 0.0f));
		vec4 topLeft     = proj * view * (tmpPos + vec4(0.0f,     tmpDim.y, 0.0f, 0.0f));

		float yOff = tmpDim.y - 20;
		float high = yOff + 2.0f;
		float dimX2 = tmpDim.x - 27.0;
		float dimX1 = 27.0f;

	// STEP 2: DRAW BOX FOR IMAGE/RECT
		if (IsHealth == 0) {
			// First Triangle
			gl_Position = topLeft;
			TexCoord = vec2(IMG_OFF[0].x / SHEET_DIM.x, IMG_OFF[0].y / SHEET_DIM.y);
			EmitVertex();

			gl_Position = topRight;
			TexCoord = vec2(IMG_OFF[0].x / SHEET_DIM.x + IMG_DIM[0].x / SHEET_DIM.x, IMG_OFF[0].y / SHEET_DIM.y);
			EmitVertex();

			gl_Position = bottomLeft;
			TexCoord = vec2(IMG_OFF[0].x / SHEET_DIM.x, IMG_OFF[0].y / SHEET_DIM.y + IMG_DIM[0].y / SHEET_DIM.y);
			EmitVertex();

			// Second Triangle
			gl_Position = topRight;
			TexCoord = vec2(IMG_OFF[0].x / SHEET_DIM.x + IMG_DIM[0].x / SHEET_DIM.x, IMG_OFF[0].y / SHEET_DIM.y);
			EmitVertex();

			gl_Position = bottomRight;
			TexCoord = vec2(IMG_OFF[0].x / SHEET_DIM.x + IMG_DIM[0].x / SHEET_DIM.x, (IMG_OFF[0].y / SHEET_DIM.y + IMG_DIM[0].y / SHEET_DIM.y));
			EmitVertex();

			gl_Position = bottomLeft;
			TexCoord = vec2(IMG_OFF[0].x / SHEET_DIM.x, IMG_OFF[0].y / SHEET_DIM.y + IMG_DIM[0].y / SHEET_DIM.y);
			EmitVertex();

	// STEP 2: OR DRAW RED HEALTH
		} else if (IsHealth == 1) {
		// Red Health
			if (TYPE[0] > 10.0f) {
				// -0.9 is width Z.
				vec4 redBL = proj * view * vec4(tmpPos.x + dimX1, tmpPos.y + yOff, 1.0f, 1.0f);
				vec4 redBR = proj * view * vec4(tmpPos.x + dimX2, tmpPos.y + yOff, 1.0f, 1.0f);
				vec4 redTR = proj * view * vec4(tmpPos.x + dimX2, tmpPos.y + high, 1.0f, 1.0f);
				vec4 redTL = proj * view * vec4(tmpPos.x + dimX1, tmpPos.y + high, 1.0f, 1.0f);
	
			// First Triangle
				gl_Position = vec4(redTL.xy, red_z, 1.0f);
				EmitVertex();
	
				gl_Position = vec4(redTR.xy, red_z, 1.0f);
				EmitVertex();
	
				gl_Position = vec4(redBL.xy, red_z, 1.0f);
				EmitVertex();
	
			// Second Triangle
				gl_Position = vec4(redTR.xy, red_z, 1.0f);
				EmitVertex();
	
				gl_Position = vec4(redBR.xy, red_z, 1.0f);
				EmitVertex();
	
				gl_Position = vec4(redBL.xy, red_z, 1.0f);
				EmitVertex();
			}

	// STEP 2: OR DRAW GREEN HEALTH
		} else if (IsHealth == 2) {
		// Green Health
			if (TYPE[0] > 10.0f) {
				float hLen   = (dimX2 - dimX1) - (HP[0] * (dimX2 - dimX1) / MAX_HP[0]);
				vec4 greenBL = proj * view * (vec4(tmpPos.x + dimX1,        tmpPos.y + yOff, 1.0f, 1.0f));
				vec4 greenBR = proj * view * (vec4(tmpPos.x + dimX2 - hLen, tmpPos.y + yOff, 1.0f, 1.0f));
				vec4 greenTR = proj * view * (vec4(tmpPos.x + dimX2 - hLen, tmpPos.y + high, 1.0f, 1.0f));
				vec4 greenTL = proj * view * (vec4(tmpPos.x + dimX1,        tmpPos.y + high, 1.0f, 1.0f));
	
			// First Triangle
				gl_Position = vec4(greenTL.xy, green_z, 1.0f);
				EmitVertex();
	
				gl_Position = vec4(greenTR.xy, green_z, 1.0f);
				EmitVertex();
	
				gl_Position = vec4(greenBL.xy, green_z, 1.0f);
				EmitVertex();
	
			// Second Triangle
				gl_Position = vec4(greenTR.xy, green_z, 1.0f);
				EmitVertex();
	
				gl_Position = vec4(greenBR.xy, green_z, 1.0f);
				EmitVertex();
	
				gl_Position = vec4(greenBL.xy, green_z, 1.0f);
				EmitVertex();
			}
		}
	}
	

	EndPrimitive();
}
