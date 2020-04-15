#version 330
#extension GL_ARB_explicit_uniform_location : require

// Take in our texture coordinate from our vertex shader
in vec2 texCoords;
// We always define a fragment color that we output.
out vec4 fragColor;

uniform sampler2D textureSampler;

layout(location=0) uniform sampler2D tex;              // our primary texture
layout(location=1) uniform sampler2D nor;              // the normal texture

void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  fragColor = texture(tex, texCoords);
}
