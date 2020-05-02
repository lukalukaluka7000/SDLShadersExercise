#version 130

in vec4 vertexColorModelPix;

out vec4 outColor;
void main(){
    outColor = vertexColorModelPix;
}