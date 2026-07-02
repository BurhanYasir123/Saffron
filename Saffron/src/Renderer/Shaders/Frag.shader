#version 330 core

in vec3 fragColor;
in vec2 TexCoords;
in float TexBool;

uniform sampler2D Texture;

out vec4 color;

void main(){
  if(TexBool > 0.0)
  {
    color = texture(Texture, TexCoords);
  } else {
    color = vec4(fragColor, 1.0f);
  }
}