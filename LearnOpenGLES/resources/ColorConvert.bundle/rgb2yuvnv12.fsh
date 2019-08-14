precision highp float;
varying vec2 v_texcoord0;
uniform sampler2D aTexture0;
uniform float width;
uniform float height;

void main()
{
    vec3 offset = vec3(0.0625, 0.5, 0.5);
    vec3 ycoeff = vec3(0.256816, 0.504154, 0.0979137);
    vec3 ucoeff = vec3(-0.148246, -0.29102, 0.439266);
    vec3 vcoeff = vec3(0.439271, -0.367833, -0.071438);
    
    vec2 nowTxtPos = v_texcoord0;
    vec2 size = vec2(width, height);
    
    // w*h*4(rgba总空间) = 0.625(u或v数据在当前fbo中所占比例);
    // 0.625:w*h/4(uv数据所占内存空间) uvlines:uv数据需要多少行
    float uvlines = 0.0625 * height; // height/16.0
    float uvlinesI = floor(uvlines);
    float uvlinesF = fract(uvlines);
    vec2 uvPosOffset = vec2(uvlinesF, uvlinesI / height);
    vec2 uMaxPos = uvPosOffset + vec2(0.0, 0.25);
    vec2 vMaxPos = uvPosOffset + uMaxPos;
    vec2 yScale = vec2(4.0, 4.0);
    vec2 uvScale = vec2(4.0, 4.0);
    if (nowTxtPos.y < 0.25)
    {
        vec2 basePos = nowTxtPos * yScale * size;
        float addY = float(int((basePos.x ) / width));
        basePos.x -= addY * width;
        basePos.y += addY;
        float y1, y2, y3, y4;
        vec2 samplingPos = basePos / size;
        vec4 texel = texture2D(aTexture0, samplingPos);
        y1 = dot(texel.rgb, ycoeff);
        y1 += offset.x;
        basePos.x += 1.0;
        samplingPos = basePos / size;
        texel = texture2D(aTexture0, samplingPos);
        y2 = dot(texel.rgb, ycoeff);
        y2 += offset.x;
        basePos.x += 1.0;
        samplingPos = basePos / size;
        texel = texture2D(aTexture0, samplingPos);
        y3 = dot(texel.rgb, ycoeff);
        y3 += offset.x;
        basePos.x += 1.0;
        samplingPos = basePos / size;
        texel = texture2D(aTexture0, samplingPos);
        y4 = dot(texel.rgb, ycoeff);
        y4 += offset.x;
        gl_FragColor = vec4(y1, y2, y3, y4);
    }
    else if (nowTxtPos.y < vMaxPos.y || (nowTxtPos.y == vMaxPos.y && nowTxtPos.x < vMaxPos.x))
    {
        nowTxtPos.y -= 0.25;
        vec2 basePos = nowTxtPos * uvScale * size;
        float addY = float(int(basePos.x / width));
        basePos.x -= addY * width;
        basePos.y += addY;
        basePos.y *= 2.0;
        basePos -= clamp(uvScale * 0.5, vec2(0.0), uvScale);
        basePos.y -= 2.0;
        vec4 texel = texture2D(aTexture0, basePos / size).rgba;
        float u1 = dot(texel.rgb, ucoeff);
        u1 += offset.y;
        texel = texture2D(aTexture0, basePos / size).rgba;
        float u2 = dot(texel.rgb, vcoeff);
        u2 += offset.y;
        basePos.x += 2.0;
        texel = texture2D(aTexture0, basePos / size).rgba;
        float u3 = dot(texel.rgb, ucoeff);
        u3 += offset.y;
        texel = texture2D(aTexture0, basePos / size).rgba;
        float u4 = dot(texel.rgb, vcoeff);
        u4 += offset.y;
        gl_FragColor = vec4(u1, u2, u3, u4);
    }
}