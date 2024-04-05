uniform sampler2D currentTexture;
uniform float time;
uniform vec2 resolution;

void main()
{
    vec4 color = texture2D(currentTexture, gl_TexCoord[0].st);

    vec2 uv = gl_TexCoord[0].st;

    vec2 center = vec2(resolution.x / 2.0, resolution.y / 2.0);

    float distance = length(uv - center);

    float glow = 0.5 + 0.5 * sin(time * 4.0 + distance * 0.1);

    vec3 baseColor = vec3(0.7, 0.2, 0.1);
    vec3 pulseColor = mix(baseColor * 0.8, baseColor * 1.2, glow);

    color.rgb *= pulseColor;

    float mask = smoothstep(0.0, 0.5, distance / center.y);

    color.a *= mask;

    gl_FragColor = color;
}
