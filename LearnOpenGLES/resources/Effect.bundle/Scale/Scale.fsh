precision highp float;
varying vec2 textureCoordinate;
uniform sampler2D inputImageTexture;

void main (void)
{
    vec4 mask = texture2D(inputImageTexture, textureCoordinate);
    gl_FragColor = vec4(mask.rgb, 1.0);
}

