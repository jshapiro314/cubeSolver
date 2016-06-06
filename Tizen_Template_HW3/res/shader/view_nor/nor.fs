precision mediump float;

uniform sampler2D s_tex0;
uniform sampler2D s_texNor;

//
uniform vec3 materialSpec, materialAmbi, materialEmit;
uniform float materialSh;
uniform vec3 sourceDiff, sourceSpec, sourceAmbi;

varying vec2 v_texCoord;
varying vec3 v_lightWS, v_viewWS;
varying mat3 tangentToWorldSpace;
//

void main() {
    // you should fill in this function
    
    //first grab the color values of each point from mapping the texture map (s_tex0) onto the
    //texture coordinates
    vec3 materialDif = texture2D(s_tex0, v_texCoord).xyz;
    //in the same way as above, grab the normal values of each point by mapping the normal
    // map (s_texNor) onto the texture coordinates. Also, we normalize the vectors returned.
    vec3 norTS = normalize(texture2D(s_texNor, v_texCoord).xyz * 2.0 - vec3(1.0));
    
    //The normal we just fected from the normal map is unfortunately in tangent space. This is a
    //problem as we will be using it in conjunction with the light direction and view which are
    //both in world space. To convert from tangent to world space, we can use the matrix we generated
    //in the vertex shader (tangentToWorldSpace). We've passed it in, and now we just multiply the
    //the normal in tangent space by it.
    vec3 normal = normalize(tangentToWorldSpace * norTS);
    
    //normalize the view and light direction vectors
    vec3 view = normalize(v_viewWS);
    vec3 S_direction = normalize(v_lightWS);
    
    //calculate the lighting based on phong model
    //Overall Formula: max(n•l, 0)S.d * M.d + (max(r•v,0))^sh S.s * M.s + S.a * M.a + M.e
    
    //calculate n•l (it'll be used multiple times)
    float normDotlight = dot(normal, S_direction);
    
    //Diffuse term (max(n•l, 0)S.d * M.d)
    float diffuseFloat = max(normDotlight, 0.0);
    vec3 diffuseTerm = diffuseFloat * sourceDiff * materialDif;
    
    //Specular term ((max(r•v,0))^sh S.s * M.s)
    vec3 reflection = 2.0 * normal * normDotlight;
    reflection = reflection - S_direction;
    vec3 specularTerm = pow(max(dot(reflection, view), 0.0), materialSh) * sourceSpec * materialSpec;
    
    //Ambient term (S.a * M.a)
    vec3 ambientTerm = sourceAmbi * materialAmbi;
    
    //Emissive term (M.e)
    vec3 emissiveTerm = materialEmit;
    
    //Total
    vec3 totalLight = diffuseTerm + specularTerm + ambientTerm + emissiveTerm;
    
    //output the color of the fragment
    gl_FragColor = vec4(totalLight, 1.0);
    
    
}
