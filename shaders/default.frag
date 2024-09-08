#version 330 core
out vec4 FragColor;

in vec3 color;
in vec3 fragNormal;
void main()
{
    // Normalize the normal and map it to RGB [0, 1]
    vec3 color = normalize(fragNormal) * 0.5 + 0.5;
    FragColor = vec4(color, 1.0); // Set the final fragment color
}