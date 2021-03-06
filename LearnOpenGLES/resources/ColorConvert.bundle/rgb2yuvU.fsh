precision highp float;
varying vec2 v_texcoord0;
uniform sampler2D aTexture0;
uniform float width;
uniform float height;
void main(void) {
    vec3 ucoeff = vec3(0.439271, -0.367833, -0.071438);
    vec2 nowTxtPos = v_texcoord0;
    vec2 texStep = vec2(1.0/width,1.0/height);
    if (v_texcoord0.x <= 0.125 && v_texcoord0.y <= 0.5) {
        vec2 newTex = v_texcoord0*vec(2.0,2.0);
        vec4 texel1 = texture2D(aTexture0, newTex*vec2(4.0,1.0) + texStep*vec2(0.0,0.0));
        vec4 texel2 = texture2D(aTexture0, newTex*vec2(4.0,1.0) + texStep*vec2(2.0,0.0));
        vec4 texel3 = texture2D(aTexture0, newTex*vec2(4.0,1.0) + texStep*vec2(4.0,0.0));
        vec4 texel4 = texture2D(aTexture0, newTex*vec2(4.0,1.0) + texStep*vec2(8.0,0.0));
        u1 = dot(texel1.rgb, ucoeff);
        u2 = dot(texel2.rgb, ucoeff);
        u3 = dot(texel3.rgb, ucoeff);
        u4 = dot(texel4.rgb, ucoeff);
        gl_FragColor = vec4(u1, u2, u3, u4);
    }
    else {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
