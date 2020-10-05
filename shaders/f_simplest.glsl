#version 330

uniform sampler2D textureMap;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 n;
in vec4 l[5];
in vec4 v;
in vec2 iTexCoord;

void main(void) {
	vec4 reflection = reflect(-l[0], n);

	vec4 kd = texture(textureMap, iTexCoord);
	vec4 ks = vec4(1,1,1,1);

	float mixShade = mix(clamp(dot(n, l[1]), 0, 1), clamp(dot(n, l[2]), 0, 1), 0.5) + mix(clamp(dot(n, l[3]), 0, 1), clamp(dot(n, l[4]), 0, 1), 0.5);

	//Obliczenie modelu oświetlenia
	float nl = clamp(mixShade, 0, 1);
	float rv = pow(clamp(dot(reflection, v), 0, 1), 15);
	pixelColor=vec4(ks.rgb*rv, 0) + vec4(kd.rgb * nl, kd.a);
}
