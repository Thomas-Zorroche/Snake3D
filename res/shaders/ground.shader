#shader vertex
#version 330 core

layout(location = 0) in vec2 positions;
uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(positions, 0.0f, 1.0f);
};

#shader fragment
#version 330 core

out vec4 color;
uniform vec3 u_color;

void main()
{
    color = vec4(u_color, 1.0f);
};