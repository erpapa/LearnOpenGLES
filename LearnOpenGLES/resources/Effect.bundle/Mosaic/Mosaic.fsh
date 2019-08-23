precision mediump float;
varying vec2 textureCoordinate;
uniform sampler2D inputImageTexture;

const vec2 TexSize = vec2(100.0, 100.0);
const vec2 mosaicSize = vec2(1.0, 1.0);

void main()
{
    vec2 intXY = vec2(textureCoordinate.x*TexSize.x, textureCoordinate.y*TexSize.y);
    vec2 XYMosaic = vec2(floor(intXY.x/mosaicSize.x)*mosaicSize.x, floor(intXY.y/mosaicSize.y)*mosaicSize.y);
    vec2 UVMosaic = vec2(XYMosaic.x/TexSize.x, XYMosaic.y/TexSize.y);
    vec4 color = texture2D(inputImageTexture, UVMosaic);
    gl_FragColor = color;
}
