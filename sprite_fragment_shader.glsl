// Source code of fragment shader
#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec2 uv_interp;

// Texture sampler
uniform sampler2D onetex;
uniform float time;
uniform int special;

float inc = 0.1;

void main()
{
    // Sample texture
    vec4 color = texture2D(onetex, uv_interp);

    if (special == 1) {
        color.r = mod(color.r + inc*time, 0.9);
        color.g = mod(color.g + inc*time, 0.9);
        color.b = mod(color.b + inc*time, 0.9);
    }

    // Assign color to fragment
    gl_FragColor = vec4(color.r, color.g, color.b, color.a);

    // Check for transparency
    if(color.a < 1.0)
    {
         discard;
    }
}
