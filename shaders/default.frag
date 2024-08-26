#version 330 core
out vec4 FragColor;

in vec3 color;
uniform float scale;
void main()
{
   FragColor = vec4(color*scale, 1.0f);
}