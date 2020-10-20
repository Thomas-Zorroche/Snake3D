#shader vertex
#version 330 core

layout(location = 0) in vec3 aPositions;
layout(location = 1) in vec3 aColors;
uniform mat4 mvp;

out vec3 Vertexcolors;

void main()
{
    gl_Position = mvp * vec4(aPositions, 1.0f);
    Vertexcolors = aColors;
};

#shader fragment
#version 330 core

in vec3 Vertexcolors;
uniform vec3 u_color;

out vec4 color;

void main()
{
    color = vec4(Vertexcolors, 1.0f);
};