#version 330
// Output fragment color
out vec4 finalColor;

in vec2 fragTexCoord;
in vec4 fragColor;

// NOTE: Add here your custom variables

// NOTE: Render size values should be passed from code
const float renderWidth = 800;
const float renderHeight = 450;

float sqr(float x) {
    return x*x;
}

void main() {
    vec2 p = fragTexCoord - vec2(0.5);
    float d = length(p) - 0.01;
    if (d < 0.0) {
        finalColor = vec4(fragColor.xyz, 1.0);
    } else {
        float a = min(1, pow(d*3, 0.1));
        finalColor = vec4(fragColor.xyz, 1-a);
    }
}
