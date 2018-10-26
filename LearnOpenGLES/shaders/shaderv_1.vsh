attribute vec4 position;
attribute vec4 sourceColor;

varying vec4 destinationColor;

void main()
{
    destinationColor = sourceColor;
    gl_Position = position;
}
