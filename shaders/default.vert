#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout(location = 3) in vec4 instanceMatrixRow1;
layout(location = 4) in vec4 instanceMatrixRow2;
layout(location = 5) in vec4 instanceMatrixRow3;
layout(location = 6) in vec4 instanceMatrixRow4;

out vec3 color;
out vec2 texCoord;

uniform mat4 cameraMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
   mat4 modelMatrix = mat4(instanceMatrixRow1,
   instanceMatrixRow2,
   instanceMatrixRow3,
   instanceMatrixRow4);

   gl_Position = cameraMatrix * modelMatrix * translation * rotation * scale * vec4(aPos, 1.0);
   color = aColor;
   texCoord = aTexCoord;
}