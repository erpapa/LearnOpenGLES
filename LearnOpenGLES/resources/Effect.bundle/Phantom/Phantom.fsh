precision highp float;
varying lowp vec2 textureCoordinate;
uniform sampler2D inputImageTexture;

varying float alphaLevel;
varying vec2 rCoord;
varying vec2 gCoord;
varying vec2 bCoord;

void main()
{
    mediump vec4 fout;
    mediump vec4 source;
	
	vec4 redOffset;
	vec4 greenOffset;
	vec4 blueOffset;
    
	source = texture2D(inputImageTexture, textureCoordinate);
	redOffset = texture2D(inputImageTexture, rCoord);
	greenOffset = texture2D(inputImageTexture, gCoord);
	blueOffset = texture2D(inputImageTexture, bCoord);
	fout = source;
	fout.r = mix(source.r, redOffset.r, alphaLevel);
	fout.g = mix(source.g, greenOffset.g, alphaLevel);
	fout.b = mix(source.b, blueOffset.b, alphaLevel);
	fout.a = 1.0;
	gl_FragColor = fout;
}
