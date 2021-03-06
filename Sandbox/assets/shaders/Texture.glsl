// Basic Texture Shader

#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;


void main()
{
	v_TexCoord = aTexCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform float u_TilingFactor;

void main()
{
	color = texture(u_Texture, v_TexCoord * u_TilingFactor) * u_Color;
}