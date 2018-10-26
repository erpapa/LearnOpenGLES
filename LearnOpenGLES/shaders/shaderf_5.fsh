precision highp float;

uniform sampler2D inputTexture;
uniform int useTexture;

varying vec4 colorVarying;
varying vec2 texCoordVarying;
varying vec4 altColorVarying;

void main() {
    if (useTexture == 1) {
        vec4 textureColor = texture2D(inputTexture, texCoordVarying);
        gl_FragColor = vec4(altColorVarying.rgb, textureColor.a);
    } else {
        gl_FragColor = altColorVarying * colorVarying;
    }
}
