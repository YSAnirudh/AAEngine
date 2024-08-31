#aa_shader_type vertex
#version 460
			
layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoords;

layout(location = 0) out vec4 color;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(Position, 1.0f);
	color = vec4(Position, 1.0f);
}
#aa_shader_type fragment
#version 460
			
layout(location = 0) out vec4 Color;

layout(location = 0) in vec4 color;

void main()
{
	Color = color;
}
