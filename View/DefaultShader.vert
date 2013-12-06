#version

//in variables
in vec3 VertexPosition;
in vec3 VertexNormal;
#version 130

//in variables
in vec3 VertexNormal;
in vec3 VertexPosition;

//uniform variables
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

//out variables
out vec3 Position;
out vec3 Normal;

void main()
{
	Normal = normalize(NormalMatrix * VertexNormal);
	Position = vec3(ModelViewMatrix * vec4(VertexPosition, 1.0));
	gl_Position = MVP * vec4(VertexPosition, 1.0);
}

