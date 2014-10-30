//#version 330 core
#version 140

out vec4 fColor;
in vec4 color;
in vec4 Position;

void main () {
	vec3 Ambient = vec3 (0.2, 0.2, 0.2);
	vec3 LightColor = vec3(1, 1, 1);
	vec3 LightPosition = vec3 (0, 2, 0);
	float Shininess = 1.0;
	float Strength = 1.0;
	vec3 lightDirection = LightPosition - vec3(Position);
	float lightDistance = sqrt (lightDirection.y*lightDirection.y 
			+ lightDirection.y*lightDirection.y + lightDirection.z*lightDirection.z);

	float attenuation = 1.0 / (0.1*lightDistance + 0.4*lightDistance*lightDistance);

	vec3 scatteredLight = Ambient + LightColor*attenuation;
	vec3 rgb = min (color.rgb * scatteredLight, vec3(1.0));

	fColor = 0.8*vec4(rgb, color.a); 
}
