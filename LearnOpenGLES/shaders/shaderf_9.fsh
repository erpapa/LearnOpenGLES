varying highp vec3 textureCoordinate;

uniform samplerCube skyboxTexture;

void main()
{
    gl_FragColor = textureCube(skyboxTexture, textureCoordinate);
}
