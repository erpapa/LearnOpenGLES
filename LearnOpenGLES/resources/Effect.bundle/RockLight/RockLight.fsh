precision highp float;
varying vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform float inputTime;

const float zMin = 0.0;
const float zMax = 0.15;
const float duration = 0.5;
const float stride = 7.0;
const float interval = 1.0;

vec2 getUV(vec2 uv, vec2 center, float zz, float zm) {
	return uv + (zz + zm) * (center - uv);
}

void main()
{
	vec4 fout;
    float percent = mod(inputTime, duration) / duration;
    float current = 8.0 - (percent * 10.0);
    if (current < 0.0) {
        current = 0.0;
    }
    float offset = 0.0875 - current * 0.0125;
    if (offset < 0.0) {
        offset = 0.0;
    }
    float ff = mod(8.0 - current, stride + interval) / stride;
    if (ff > 1.0) {
        ff = 0.0;
    }
	float zz = pow(ff, 3.0) * 1.125 * (zMax - zMin);
	float coeff = pow(zz, 0.75);
	fout.r = texture2D(inputImageTexture, getUV(textureCoordinate, vec2(0.5, 0.5), zz, zMin) + vec2(0.0, -offset) * coeff).r;
	fout.g = texture2D(inputImageTexture, getUV(textureCoordinate, vec2(0.5, 0.5), zz, zMin) + vec2(-offset, 0.0) * coeff).g;
	fout.b = texture2D(inputImageTexture, getUV(textureCoordinate, vec2(0.5, 0.5), zz, zMin) + vec2(0.0, -offset) * coeff).b;
	gl_FragColor = fout;
}
