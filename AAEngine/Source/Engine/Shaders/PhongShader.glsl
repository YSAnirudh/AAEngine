#aa_shader_type vertex
#version 460

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
//layout(location = 2) in vec2 TexCoord;

//out vec3 OutNormal;

uniform mat4 MVPMatrix;

void main()
{
	gl_Position = MVPMatrix * vec4(Position, 1.0f);
	gl_Position.z = -gl_Position.z;
}

#aa_shader_type fragment
#version 460

//layout(location = 0) in vec3 OutNormal;
out vec4 Color;

//vec3 LightDirection;

void main()
{
	vec3 Ambient = vec3(1.0);
	vec3 Diffuse = vec3(0.0);
	vec3 Specular;

	//vec3 FinalColor = vec3(1.0, 1.0, 1.0) * (Ambient);

	Color = vec4(1.0);
}
