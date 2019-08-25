precision highp float;
varying highp vec2 textureCoordinate;

uniform sampler2D inputImageTexture;

void main()
{
    vec4 texColor = texture2D(inputImageTexture, textureCoordinate);
    if (texColor.a < 0.10) { // 丢弃轨道纹理的透明部分（ALPHA_TEST）
        discard;
    }
    gl_FragColor = texColor;
}
