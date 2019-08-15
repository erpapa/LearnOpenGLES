precision highp float;

uniform int ScreenType;
uniform sampler2D Texture;
varying vec2 TextureCoordsVarying;

void main()
{
    vec2 uv = TextureCoordsVarying;
    
    // 1
    if (ScreenType == 0) {
        
    } else if (ScreenType == 1) {
        // 2 v
        if (uv.y <= 0.5) {
            uv.y = uv.y + 0.25;
        } else {
            uv.y = uv.y - 0.25;
        }
    } else if (ScreenType == 2) {
        // 2 h
        if (uv.x <= 0.5) {
            uv.x = uv.x + 0.25;
        } else {
            uv.x = uv.x - 0.25;
        }
    } else if (ScreenType == 3) {
        // 3v
        if (uv.y <= 1.0/3.0) {
            uv.y = uv.y + 1.0/3.0;
        } else if (uv.y >= 2.0/3.0) {
            uv.y = uv.y - 1.0/3.0;
        }
    } else if (ScreenType == 4) {
        // 3h
        if (uv.x <= 1.0/3.0) {
            uv.x = uv.x + 1.0/3.0;
        } else if (uv.x >= 2.0/3.0) {
            uv.x = uv.x - 1.0/3.0;
        }
    } else if (ScreenType == 7) {
        // 4
        if (uv.x <= 0.5) {
            uv.x = uv.x + 0.25;
        } else {
            uv.x = uv.x - 0.25;
        }
        if (uv.y <= 0.5) {
            uv.y = uv.y + 0.25;
        } else {
            uv.y = uv.y - 0.25;
        }
    } else if (ScreenType == 8) {
        // 6v
        if (uv.x <= 0.5) {
            uv.x = uv.x + 0.25;
        } else {
            uv.x = uv.x - 0.25;
        }
        if (uv.y <= 1.0/3.0) {
            uv.y = uv.y + 1.0/3.0;
        } else if (uv.y >= 2.0/3.0) {
            uv.y = uv.y - 1.0/3.0;
        }

    } else if (ScreenType == 9) {
        // 6h
        if (uv.x <= 1.0/3.0) {
            uv.x = uv.x + 1.0/3.0;
        } else if (uv.x >= 2.0/3.0) {
            uv.x = uv.x - 1.0/3.0;
        }
        if (uv.y <= 0.5) {
            uv.y = uv.y + 0.25;
        } else {
            uv.y = uv.y - 0.25;
        }
    } else if (ScreenType == 10) {
        // 9
        if (uv.x <= 1.0/3.0) {
            uv.x = uv.x + 1.0/3.0;
        } else if (uv.x >= 2.0/3.0) {
            uv.x = uv.x - 1.0/3.0;
        }
        if (uv.y <= 1.0/3.0) {
            uv.y = uv.y + 1.0/3.0;
        } else if (uv.y >= 2.0/3.0) {
            uv.y = uv.y - 1.0/3.0;
        }
    }
    
    vec4 textureColor = texture2D(Texture, uv);
    
    if (ScreenType == 5) {
        // 3 blur
        if (uv.y <= 1.0/3.0 || uv.y >= 2.0/3.0) {
            // blurry cal
            vec2 center = vec2(0.5, 0.5);
            uv -= center;
            uv = uv / 1.5;
            uv += center;
            vec4 whiteMask = vec4(0.5, 0.5, 0.5, 0.9);
            textureColor = mix(whiteMask, texture2D(Texture, uv) * 0.5, 0.2);
        }
    } else if (ScreenType == 6) {
        // 3black
        if (uv.y <= 1.0/3.0 || uv.y >= 2.0/3.0) {
            // blurry cal
            vec3 W = vec3(0.2125, 0.7154, 0.0721);
            float luminance = dot(textureColor.rgb, W);
            
            // mix gary
            vec4 whiteMask = vec4(0.5, 0.5, 0.5, 0.9);
            textureColor = vec4(vec3(luminance), textureColor.a);
            textureColor = mix(whiteMask, textureColor, 0.5);
        }
    }
    gl_FragColor = textureColor;
}