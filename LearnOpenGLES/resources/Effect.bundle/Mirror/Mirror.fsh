precision highp float;
varying vec2 textureCoordinate;
uniform sampler2D inputImageTexture;

uniform float inputTime;
const float duration = 3.0;

void main()
{
    float currentTime = mod(inputTime, duration);
	highp vec2 position = textureCoordinate;
    if (currentTime <= 1.0) {
        position.x = position.x;
    } else if (currentTime <= 2.0) {
		if (position.x > 0.5) {
			position.x = 1.0 - position.x;
		}
	} else {
		if (position.x > 0.5) {
			position.x = position.x - 0.5;
		} else {
			position.x = 0.5 - position.x;
		}
	}
	gl_FragColor = texture2D(inputImageTexture, position);
}
