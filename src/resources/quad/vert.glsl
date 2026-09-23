//iris_replace_glsl_version
precision highp float;
layout (location = 0) in vec2 a_pos;
uniform vec2 iris_pos;
uniform vec2 iris_size;
void main() {
    vec2 normalized = iris_pos + a_pos * iris_size;

    vec2 ndc = vec2(
        normalized.x * 2.0 - 1.0,
        1.0 - normalized.y * 2.0
    );

    gl_Position = vec4(ndc.x, ndc.y, 1.0, 1.0);
}
