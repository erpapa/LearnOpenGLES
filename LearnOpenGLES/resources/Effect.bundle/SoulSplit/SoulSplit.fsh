precision mediump float;
varying vec2 textureCoordinate;
uniform sampler2D inputImageTexture;

uniform float inputTime;
const float duration = 3.0;

void main()
{
    float time = mod(inputTime, duration);
	if (time <= 1.0) {
		gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
	} else if (time <= 2.0) {
        float x = textureCoordinate.x * 2.0;
        float y = textureCoordinate.y * 2.0;
        gl_FragColor = texture2D(inputImageTexture, vec2(x - floor(x), y - floor(y)));
    } else if (time <= 3.0) {
        float x = textureCoordinate.x * 3.0;
        float y = textureCoordinate.y * 3.0;
        gl_FragColor = texture2D(inputImageTexture, vec2(x - floor(x), y - floor(y)));
    }
}
