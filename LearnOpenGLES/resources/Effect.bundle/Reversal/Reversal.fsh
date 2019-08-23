precision highp float;
varying vec2 textureCoordinate;
uniform sampler2D inputImageTexture;

void main (void)
{
    vec4 color = texture2D(inputImageTexture, vec2(1.0 - textureCoordinate.x, 1.0 - textureCoordinate.y));
    gl_FragColor = color;
}
