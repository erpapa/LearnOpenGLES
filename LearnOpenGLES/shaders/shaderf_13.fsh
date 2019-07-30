precision highp float;
varying highp vec2 textureCoordinate;

uniform sampler2D inputImageTexture;

void main()
{
    vec4 texColor = texture2D(inputImageTexture, textureCoordinate);
    if (texColor.a < 0.5) { // alpha小于0.5则丢弃
        discard;
    }
    gl_FragColor = texColor;
}
