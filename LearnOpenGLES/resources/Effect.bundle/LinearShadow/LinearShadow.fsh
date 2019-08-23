precision mediump float;
varying highp vec2 textureCoordinate;
uniform sampler2D inputImageTexture;

uniform float inputTime;
const float duration = 0.7;
const float c = -0.015;
const float mode = 0.0;
const float alpha = 0.0;

void main()
{
    float percent = mod(inputTime, duration) / duration;
    float width = 0.003 + 0.003 * percent;
    float stride = 0.015 + 0.015 * percent;
    vec4 color = texture2D(inputImageTexture, textureCoordinate);
    float mx = mod(textureCoordinate.x + c, stride);
    if ((mode < 0.5 && mx <= width) || (mode > 0.5 && (mx > width))) {
        gl_FragColor = vec4(color.rgb * alpha, color.a);
    } else {
        gl_FragColor = color;
    }
}
