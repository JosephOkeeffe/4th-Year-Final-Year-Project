// Declare the input variables
uniform sampler2D currentTexture;  // Texture sampler for the current texture
uniform float time;                 // Time passed since the start of the application
uniform vec2 resolution;            // Resolution of the screen

// The main function, executed for each pixel of the texture
void main()
{
    // Calculate the UV coordinates of the current pixel
    vec2 uv = gl_TexCoord[0].st;

    // Calculate the center of the screen
    vec2 center = vec2(resolution.x / 2.0, resolution.y / 2.0);

    // Calculate the distance from the center to the current pixel
    float distance = length(uv - center);

    // Calculate the glow intensity based on distance, time, and a sine function
    float glow = 0.5 + 0.5 * sin(time * 4.0 + distance * 0.1);

    // Define the base color of the sprite by sampling from the texture
    vec4 baseColor = texture2D(currentTexture, uv);

    // Define the color of the specular highlight (a bright spot on the sprite)
    vec3 specularColor = vec3(1.0); // White specular color

    // Adjust the shininess factor, controlling the size of the specular highlight
    float shininess = 8.0; // Higher values result in smaller highlights

    // Calculate the intensity of the specular highlight based on the angle between the light direction and surface normal
    float specularIntensity = pow(max(dot(normalize(vec3(0.5, 0.5, 1.0)), normalize(vec3(uv - center, 1.0))), 0.0), shininess);

    // Scale the specular color by the intensity to get the final specular highlight color
    vec3 finalSpecular = specularColor * specularIntensity;

    // Apply the specular highlight to the base color with reduced intensity
    vec4 finalColor = baseColor + vec4(finalSpecular * glow * 0.3, 0.0); // Adjust the glow intensity factor

    // Apply additive blending to achieve the animated glow effect
    gl_FragColor = finalColor;
}
