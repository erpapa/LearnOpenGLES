precision mediump float;
varying vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform vec2 inputTextureSize;

const mat3 xKernal = mat3(-1.0, 0.0, 1.0, -2.0, 0.0, 2.0, -1.0, 0.0, 1.0);
const mat3 yKernal = mat3(1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0);
const vec3 LW = vec3(0.2125, 0.7154, 0.0721);
float gray[9];
vec2 offsets[9];

float convolution3x3(mat3 kernal) {
	float v = gray[0] * kernal[0][0];
	v += gray[1] * kernal[0][1];
	v += gray[2] * kernal[0][2];
	v += gray[3] * kernal[1][0];
	v += gray[4] * kernal[1][1];
	v += gray[5] * kernal[1][2];
	v += gray[6] * kernal[2][0];
	v += gray[7] * kernal[2][1];
	v += gray[8] * kernal[2][2];
	return v;
}

void main()
{
	offsets[0] = vec2(-1.0, 1.0);
	offsets[1] = vec2(0.0, 1.0);
	offsets[2] = vec2(1.0, 1.0);
	offsets[3] = vec2(-1.0, 0.0);
	offsets[4] = vec2(0.0, 0.0);
	offsets[5] = vec2(1.0, 0.0);
	offsets[6] = vec2(-1.0, -1.0);
	offsets[7] = vec2(0.0, -1.0);
	offsets[8] = vec2(1.0, -1.0);
	vec2 _step = vec2(1.0 / inputTextureSize.x, 1.0 / inputTextureSize.y);
	for (int i = 0; i < 9; ++i) {
		gray[i] = dot(texture2D(inputImageTexture, textureCoordinate + _step * offsets[i]).xyz, LW);
	}
	vec2 G = vec2(convolution3x3(xKernal), convolution3x3(yKernal));
	gl_FragColor = vec4(vec3(length(G)), 1.0);
}
