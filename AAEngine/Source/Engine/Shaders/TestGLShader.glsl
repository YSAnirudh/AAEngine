#aa_shader_type vertex
#version 460
			
layout(location = 0) in vec3 Position;

out vec4 color;

uniform mat4 MVPMatrix;

void main()
{
	gl_Position = MVPMatrix * vec4(Position, 1.0f);
	color = vec4(Position, 1.0f);
	gl_Position.z = -gl_Position.z;
}
#aa_shader_type fragment
#version 460
			
layout(location = 0) out vec4 Color;

in vec4 color;

void main()
{
	Color = color;
}
