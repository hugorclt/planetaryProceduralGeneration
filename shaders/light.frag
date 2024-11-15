#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 FragPos;
in vec4 aPosition;

vec4 firstColor = vec4(0.07, 0.48, 0.65, 1.0); // blue
vec4 middleColor = vec4(0.2, 0.6, 0.4, 1.0);   // green
vec4 endColor = vec4(0.52, 0.26, 0.0, 1.0);    // brown

void main()
{
    float ambientStrength = 1.0;
    vec3 ambient = ambientStrength * lightColor;

    // Lighting calculations
    vec3 normal = vec3(0.0, 1.0, 0.0);
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    // Set the range for y to control gradient transitions
    float minY = -10.0; // The lowest y-value for the gradient start
    float maxY = 10.0; // The highest y-value for the gradient end

    // Normalize the y position to a 0 to 1 range
    float normalizedY = clamp((aPosition.y - minY) / (maxY - minY), 0.0, 1.0);

    // Define points for the gradient to allocate more space for the middle color
    float startMiddle = 0.3; // where to start blending to the middle color
    float endMiddle = 0.7;   // where to start blending to the end color

    vec4 col;
    if (normalizedY < startMiddle) {
        // Blend quickly between firstColor and middleColor
        col = mix(firstColor, middleColor, normalizedY / startMiddle);
    } else if (normalizedY < endMiddle) {
        // Keep middleColor longer by setting it directly
        col = middleColor;
    } else {
        // Blend between middleColor and endColor
        col = mix(middleColor, endColor, (normalizedY - endMiddle) / (1.0 - endMiddle));
    }

    // Final color with lighting
    vec3 result = (diffuse + ambient) * col.rgb;
    FragColor = vec4(result, 1.0);
}

