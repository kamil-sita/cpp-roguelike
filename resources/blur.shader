uniform sampler2D texture;
uniform float blur_radius;

void main() {
    vec2 offx = vec2(blur_radius, 0.0);
    vec2 offy = vec2(0.0, blur_radius);

    /**
     * Automatically generated blur shader based on gaussian blur.
     */

    vec4 pixel =
            texture2D(texture, gl_TexCoord[0].xy + (-5) * offx + (-5) * offy) * 1.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-5) * offx + (-4) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-5) * offx + (-3) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-5) * offx + (-2) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-5) * offx + (-1) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-5) * offx + (0) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-5) * offx + (1) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-5) * offx + (2) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-5) * offx + (3) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-5) * offx + (4) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-5) * offx + (5) * offy) * 1.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-4) * offx + (-5) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-4) * offx + (-4) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-4) * offx + (-3) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-4) * offx + (-2) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-4) * offx + (-1) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-4) * offx + (0) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-4) * offx + (1) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-4) * offx + (2) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-4) * offx + (3) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-4) * offx + (4) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-4) * offx + (5) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-3) * offx + (-5) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-3) * offx + (-4) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-3) * offx + (-3) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-3) * offx + (-2) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-3) * offx + (-1) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-3) * offx + (0) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-3) * offx + (1) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-3) * offx + (2) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-3) * offx + (3) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-3) * offx + (4) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-3) * offx + (5) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-2) * offx + (-5) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-2) * offx + (-4) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-2) * offx + (-3) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-2) * offx + (-2) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-2) * offx + (-1) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-2) * offx + (0) * offy) * 16.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-2) * offx + (1) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-2) * offx + (2) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-2) * offx + (3) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-2) * offx + (4) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-2) * offx + (5) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-1) * offx + (-5) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-1) * offx + (-4) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-1) * offx + (-3) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-1) * offx + (-2) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-1) * offx + (-1) * offy) * 16.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-1) * offx + (0) * offy) * 23.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-1) * offx + (1) * offy) * 16.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-1) * offx + (2) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-1) * offx + (3) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-1) * offx + (4) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (-1) * offx + (5) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (0) * offx + (-5) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (0) * offx + (-4) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (0) * offx + (-3) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (0) * offx + (-2) * offy) * 16.0 +
            texture2D(texture, gl_TexCoord[0].xy + (0) * offx + (-1) * offy) * 23.0 +
            texture2D(texture, gl_TexCoord[0].xy + (0) * offx + (0) * offy) * 32.0 +
            texture2D(texture, gl_TexCoord[0].xy + (0) * offx + (1) * offy) * 23.0 +
            texture2D(texture, gl_TexCoord[0].xy + (0) * offx + (2) * offy) * 16.0 +
            texture2D(texture, gl_TexCoord[0].xy + (0) * offx + (3) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (0) * offx + (4) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (0) * offx + (5) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (1) * offx + (-5) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (1) * offx + (-4) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (1) * offx + (-3) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (1) * offx + (-2) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (1) * offx + (-1) * offy) * 16.0 +
            texture2D(texture, gl_TexCoord[0].xy + (1) * offx + (0) * offy) * 23.0 +
            texture2D(texture, gl_TexCoord[0].xy + (1) * offx + (1) * offy) * 16.0 +
            texture2D(texture, gl_TexCoord[0].xy + (1) * offx + (2) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (1) * offx + (3) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (1) * offx + (4) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (1) * offx + (5) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (2) * offx + (-5) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (2) * offx + (-4) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (2) * offx + (-3) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (2) * offx + (-2) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (2) * offx + (-1) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (2) * offx + (0) * offy) * 16.0 +
            texture2D(texture, gl_TexCoord[0].xy + (2) * offx + (1) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (2) * offx + (2) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (2) * offx + (3) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (2) * offx + (4) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (2) * offx + (5) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (3) * offx + (-5) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (3) * offx + (-4) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (3) * offx + (-3) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (3) * offx + (-2) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (3) * offx + (-1) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (3) * offx + (0) * offy) * 12.0 +
            texture2D(texture, gl_TexCoord[0].xy + (3) * offx + (1) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (3) * offx + (2) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (3) * offx + (3) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (3) * offx + (4) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (3) * offx + (5) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (4) * offx + (-5) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (4) * offx + (-4) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (4) * offx + (-3) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (4) * offx + (-2) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (4) * offx + (-1) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (4) * offx + (0) * offy) * 8.0 +
            texture2D(texture, gl_TexCoord[0].xy + (4) * offx + (1) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (4) * offx + (2) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (4) * offx + (3) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (4) * offx + (4) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (4) * offx + (5) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (5) * offx + (-5) * offy) * 1.0 +
            texture2D(texture, gl_TexCoord[0].xy + (5) * offx + (-4) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (5) * offx + (-3) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (5) * offx + (-2) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (5) * offx + (-1) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (5) * offx + (0) * offy) * 6.0 +
            texture2D(texture, gl_TexCoord[0].xy + (5) * offx + (1) * offy) * 4.0 +
            texture2D(texture, gl_TexCoord[0].xy + (5) * offx + (2) * offy) * 3.0 +
            texture2D(texture, gl_TexCoord[0].xy + (5) * offx + (3) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (5) * offx + (4) * offy) * 2.0 +
            texture2D(texture, gl_TexCoord[0].xy + (5) * offx + (5) * offy) * 1.0;

     gl_FragColor =  gl_Color * (pixel / 816.0);
}