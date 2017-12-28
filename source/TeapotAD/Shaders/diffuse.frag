#version 430

in vec3 vertPos;
in vec3 N;
in vec3 lightPos;


uniform vec3 Ka;			// Ambient 
uniform vec3 La;			// Ambient 
uniform vec3 Kd;            // Diffuse reflectivity
uniform vec3 Ld;            // Diffuse light intensity
uniform vec3 Ks;			// Specular
uniform vec3 Ls;			// Specular

layout( location = 0 ) out vec4 FragColour;

void main() {
   vec4 la = vec4(La,1.0) * vec4(Ka,1.0);

   //Calculate the light vector
   vec3 L = normalize(lightPos - vertPos);  
    
   //calculate Diffuse Light Intensity making sure it is not negative 
   //and is clamped 0 to 1  
   vec4 ld = vec4(Ld,1.0) * max(dot(N,L), 0.0);
   ld = clamp(ld, 0.0, 1.0);   
   ld = vec4(Kd, 1.0) * ld;
   vec3 Dist = lightPos - vertPos;
   
   float d = sqrt((Dist.x * Dist.x) + (Dist.y * Dist.y) + (Dist.z * Dist.z));
   d = d / 25;
   float Fatt = 1/(d*d);
   Fatt = clamp(Fatt, 0.0, 1.0);
   float n = 2;
   vec4 R = vec4(normalize(reflect(L,normalize(N))),1.0);
   vec4 V = vec4(normalize(vertPos),1.0);
   vec4 ls = vec4(Ls,1.0) * vec4(Ks,1.0) * pow(max(dot(R,V),0.0),n);  

   //Multiply the Reflectivity by the Diffuse intensity
   FragColour = la + (Fatt * ld) + (Fatt * ls);

}
