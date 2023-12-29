#type FRAGMENT_SHADER
#version 450 core

layout(location = 0) out vec4 color;

in vec2 C;

vec2 f(vec2 C)
{
    return C;

}

void main()
{
    color = vec4(f(C).x, 0.0, 0.0, 1.0);

}
