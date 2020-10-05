#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 normal; //wektor normalny w przestrzeni modelu
in vec2 texCoord;

//Zmienne interpolowane
out vec4 l[5];
out vec4 n;
out vec4 v;
out vec2 iTexCoord;

void calcLightParams(int lightIndex, vec4 position) {
    l[lightIndex] = normalize(V * position - V*M*vertex); //wektor do światła
}

void main(void) {
    calcLightParams(0, vec4(0, 30, 0, 1));
    calcLightParams(1, vec4(-70, 30, 0, 1));
    calcLightParams(2, vec4(70, 30, 0, 1));
    calcLightParams(3, vec4(0, 30, -70, 1));
    calcLightParams(4, vec4(0, 30, 70, 1));

    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //wektor do obserwatora
    n = normalize(V * M * normal); //wektor normalny

    iTexCoord = texCoord;

    gl_Position=P*V*M*vertex;
}
