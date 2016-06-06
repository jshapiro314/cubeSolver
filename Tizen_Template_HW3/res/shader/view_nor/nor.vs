
uniform mat4 worldMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat4 invTransWorldMat;

uniform vec3 eyePos;
uniform vec3 lightPos;

attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord;
attribute vec3 tangent;

varying vec2 v_texCoord;
varying vec3 v_lightWS;
varying vec3 v_viewWS;
varying mat3 tangentToWorldSpace;

void main() {
   // you should fill in this function
    
    //create 4d vector to hold vector after transform from position to world (typically just part
    //of gl_Position, but will be used again so easier to give it a variable
    vec4 posWS = worldMat * vec4(position, 1.0);
    
    //calculate gl_Position as we have done before (transform of vertices to clip space)
    gl_Position = projMat * viewMat * posWS;
    
    //pass text coordinates from vertex shader to fragment shader
    v_texCoord = texCoord;
    
    
    //create our matrix transform to convert from tangent space to object space.
    vec3 nor = mat3(worldMat) * normal;
    vec3 tan = mat3(worldMat) * normalize(tangent);
    vec3 bin = cross(nor, tan);
    //create matrix of the following form (keeping in mind GLSL uses column major order):
    //  tan.x|bin.x|nor.x
    //  tan.y|bin.y|nor.y
    //  tan.z|bin.z|nor.z
    mat3 tangentToObjectSpace = mat3(tan.x, tan.y, tan.z, bin.x, bin.y, bin.z, nor.x, nor.y, nor.z);
    //Now we need to create the matrix that will convert from tangent space to world space.
    //this is done by multiplying the tangentToObjectSpace matrix by the invTransWorldMatrix
    tangentToWorldSpace =  tangentToObjectSpace * mat3(invTransWorldMat);
    
    
    //Calculate the light and view vectors in world space (simply subtract position vector
    //in world space from both light and eye).
    v_lightWS = lightPos - posWS.xyz;
    v_viewWS = eyePos - posWS.xyz;
}