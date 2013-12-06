#version 130

//in variables
in vec3 Position;
in vec3 Normal;

//uniform variables
uniform vec4 lightPosition[6];
uniform vec4 lightIntensity[6];
uniform vec3 Ka;
uniform vec3 Ks;
uniform vec3 Kd;
uniform float Shininess;
uniform int numLights;

//out variables
out vec4 FragColor;

vec3 phong()
{
	vec3 n = normalize(Normal);
	vec3 result = vec3(0.0, 0.0, 0.0);
	for(int i = 0; i < numLights; ++i)
	{
		vec3 s = normalize(vec3(lightPostion[i] - Position));
		vec3 v = normalize(-Position);
		vec3 r = reflect(-s, n);
		result += vec3(lightIntensity[i]) * (Kd * max(dot(s,n), 0.0) + Ks * pow(max(dot(r,v), 0.0), Shininess);
	}
	result += Ka;
	result /= numLights;
	return result;
}

void main()
{
	FragColor = vec4(phong(), 1.0);
}
