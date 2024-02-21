uniform sampler2D currentTexture;
uniform float time;
uniform vec2 resolution;
#define PI 3.14159265359

float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Smooth interpolation
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
           (c - a) * u.y * (1.0 - u.x) +
           (d - b) * u.x * u.y;
}

void main() {
    vec2 uv = gl_TexCoord[0].st * 5.0;  // Adjust the multiplier for frequency
    vec2 distortedUV = uv + vec2(0.0, sin(uv.x * 10.0 + time * 2.0) * 0.05);  // Adjust the frequency and amplitude

    float n = noise(distortedUV);

    // Adjust fog color and intensity
    vec3 fogColor = vec3(0.0, 0.0, 0.0);  // Black fog color
    float fogIntensity = 0.3;  // Adjust intensity as needed

    // Apply the fog effect
    vec3 color = mix(fogColor, vec3(0.5, 0.5, 0.5) * n, fogIntensity);  // Grey fog

    gl_FragColor = vec4(color, 1.0);
}
