#type FRAGMENT_SHADER
#version 450 core

layout (location = 0) out vec4 out_color;

in vec2 C;

layout (binding = 0) uniform sampler2D u_field;


void main()
{
    out_color = vec4(texture(u_field, C).xy, 0.0, 1.0);

}