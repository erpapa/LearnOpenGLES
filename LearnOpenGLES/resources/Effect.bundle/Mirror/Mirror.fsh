precision highp float;

uniform sampler2D Texture;
varying highp vec2 TextureCoordsVarying;
uniform float Time;

void main() {
    float duration = 3.0;
    float time = mod(Time, duration);
    
	highp vec2 position = TextureCoordsVarying;
    if (time <= 1.0) {
        position.x = position.x;
    } else if (time <= 2.0) {
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
	gl_FragColor = texture2D(Texture, position);
}
