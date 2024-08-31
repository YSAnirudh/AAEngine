#aa_shader_type vertex
#version 460

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
//layout(location = 2) in vec2 TexCoord;

//out vec3 OutNormal;

uniform mat4 MVPMatrix;

void main()
{
	mat4 Transform;
	Transform[0] = vec4(0, 0, -1, 0);
	Transform[1] = vec4(1, 0, 0, 0);
	Transform[2] = vec4(0, 1, 0, 0);
	Transform[3] = vec4(0, 0, 0, 1);

	mat4 TransMVPMatrix = MVPMatrix * Transform;

	gl_Position = TransMVPMatrix * vec4(Position, 1.0f);
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
