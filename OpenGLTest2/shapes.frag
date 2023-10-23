#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
uniform vec4 ourColor;
void main()
{
    //FragColor= vec4(1.0f, 0.6f, 0.4f, 1.0f);
    FragColor=vec4(ourColor.xyz,1.0f);
}
