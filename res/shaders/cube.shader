#shader vertex
#version 330 core

layout(location = 0) in vec3 aPositions;
layout(location = 1) in float aShadow;

uniform mat4 mvp;

out float Shadow;

void main()
{
    gl_Position = mvp * vec4(aPositions, 1.0f);
    Shadow = aShadow;
};

#shader fragment
#version 330 core

in float Shadow;
uniform vec3 u_color;

out vec4 color;

void main()
{
    float shadowFactor = 0.5f;
    vec3 NewColor = u_color;
    // Shadow
    if (Shadow > 0.5f)
    {
        NewColor.r *= shadowFactor;
        NewColor.g *= shadowFactor;
        NewColor.b *= shadowFactor;
    }
    color = vec4(NewColor, 1.0f);
};