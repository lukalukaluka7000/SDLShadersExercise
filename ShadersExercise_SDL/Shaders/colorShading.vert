#version 130

//what are our inputs
in vec4 vertexPositionModel; // _colorProgram.addAttribute("vertexPosition");
in vec4 vertexColorModel;    // _colorProgram.addAttribute("vertexColor
in vec3 vertexNormalModel;
//in vec2 vertexUV;       //novi atribut takoder


uniform mat4 projection;    // View to Projector
uniform mat4 view;          // World to View
uniform mat4 model;         // Model to World

// ---klasicno slanje fragment colora
//out vec3 fragmentColor;

// ---slanje normale i pozicije u fragment shader, we dont get that for free
out vec3 vertexPositionWorld;
out vec3 vertexNormalWorld;
out vec3 vertexColorModelPix;

void main(){
    //gl_Position.xy = (P * vec4(vertexPosition.xy, 0.0, 1.0)).xy;
    
    
    //gl_Position.xy = vertexPosition.xy; //squizling
    //gl_Position.z = 0.0;
    //gl_Position.w = 1.0;
    gl_Position = projection * view * model * vertexPositionModel;
    
    //fragmentColor = vertexColor.xyz;
    //fragmentColor = vertexNormal;
    // --- in projection Space looks Kinda nice
    //fragmentColor = gl_Position.xyz;    
    
    // ---klasicni deffuse light u per vertex paradigmi
    //vec3 l = normalize(lightPosition - vertexPosition.xyz);
    //float brightness = dot(l,vertexNormal);
    //fragmentColor = ambient.xyz + vertexColor.xyz * dot(l,vertexNormal);
    //fragmentColor = vec3(brightness, brightness, brightness);
    //theNormal = vertexNormal.xyz;
    vertexNormalWorld   = vec3(model * vec4(vertexNormalModel, 0));
    vertexPositionWorld = vec3(model * vertexPositionModel);
    vertexColorModelPix = vertexColorModel.xyz;
}