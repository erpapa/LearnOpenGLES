precision highp float;
varying vec2 textureCoordinate;
uniform sampler2D inputImageTexture;

uniform float inputTime;
const float duration = 1.25;

void main()
{
    float currentTime = mod(inputTime, duration);
    vec4 sourceColor = texture2D(inputImageTexture, textureCoordinate);

    if ((currentTime > 0.5 && currentTime < 0.625) || (currentTime > 1.0 && currentTime < 1.25)) {
    	gl_FragColor  = vec4((1.0 - sourceColor.rgb), sourceColor.a);
    } else {
    	gl_FragColor = sourceColor;
    }
}
