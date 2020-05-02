#version 130

//out vec3 color;

//uniform float time;
//uniform sampler2D mySampler;

//in vec3 fragmentColor;
uniform vec4 ambientLight;

in vec3 vertexNormalWorld;
in vec3 vertexPositionWorld;

in vec3 vertexColorModelPix;

uniform vec3 eyePositionWorld;
uniform vec3 lightPositionWorld;

out vec4 outColor;

void main(){
    //get the color from a texture
    
    //drugi par korinate for our pixel (u,v)->[0,1]
    //vec4 textureColor = texture(mySampler, fragmentUV);
    
    //gl_FragColor = vec4(fragmentColor, 1.0);
    
    // ---diffuse light
    vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
    float brightness = dot(lightVectorWorld, normalize(vertexNormalWorld));
    //fragmentColor = ambient.xyz + vertexColor.xyz * dot(l,vertexNormal);
    vec4 diffuseLight = vec4(brightness, brightness, brightness, 1.0);

    // ---sepcular light
    vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, vertexNormalWorld);
    vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
    float s = clamp(dot(reflectedLightVectorWorld, eyeVectorWorld), 0, 1);
    s = pow(s, 50);
    vec4 specularLight = vec4(0,0,s,1);
    
    float distanceLightPosWorld = length(lightPositionWorld - vertexPositionWorld);
    
    outColor = /*vec4(vertexColorModelPix,1.0) **/ 
            (
            ambientLight + 
            ((clamp(diffuseLight, 0, 1) + clamp(specularLight,0, 1)) / (distanceLightPosWorld + 1))
            );
    
    //color = textureColor * fragmentColor; // color blending
    
    //color = vec4(fragmentColor.r * (sin(fragmentPosition.y  + time) + 1.0) * 0.5,
    //             fragmentColor.g * (300*sin(fragmentPosition.y  + time) + 1.0) * 0.5,
    //             fragmentColor.b * (600*sin(fragmentPosition.x  + 1.0) * 0.5, fragmentColor.a)+ textureColor * time);
    //             

    //color = vec4(100*time/(2*time), 0.5, 100*time/(2*time) , fragmentColor.a)* textureColor;
} 