#version 400 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    //FragColor = texture(ourTexture, TexCoord);

    vec4 textureColor = texture(ourTexture, TexCoord);
    if (textureColor == vec4(0.0, 0.0, 0.0, 1.0)) {
        discard;
    }
    FragColor = textureColor;
}
