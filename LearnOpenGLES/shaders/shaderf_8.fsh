precision highp float;
varying highp vec2 textureCoordinate;

uniform sampler2D inputImageTexture;

void main()
{
    vec4 texColor = texture2D(inputImageTexture, textureCoordinate);
    if (texColor.a < 0.10) { // 丢弃轨道图片中的透明部分
        discard;
    }
    gl_FragColor = texColor;
}
