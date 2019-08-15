precision highp float;

uniform sampler2D Texture;
varying vec2 TextureCoordsVarying;

uniform float Time;
const float duration = 1.25;

void main() {
    float currentTime = mod(Time, duration);
    vec4 sourceColor = texture2D(Texture, TextureCoordsVarying);

    if ((currentTime > 0.5 && currentTime < 0.625) || (currentTime > 1.0 && currentTime < 1.25)) {
    	gl_FragColor  = vec4((1.0 - sourceColor.rgb), sourceColor.a);
    } else {
    	gl_FragColor = sourceColor;
    }
}
