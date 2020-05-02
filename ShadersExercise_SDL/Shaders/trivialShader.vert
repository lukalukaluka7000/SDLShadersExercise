#version 130

in vec4 vertexPositionModel;
in vec4 vertexColorModel;


uniform mat4 projection;    // View to Projector
uniform mat4 view;          // World to View
uniform mat4 model;         // Model to World


out vec4 vertexColorModelPix;

void main(){
    gl_Position = projection*view*model*vertexPositionModel;
    
    vertexColorModelPix = vertexColorModel;
}