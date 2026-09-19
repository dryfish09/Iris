file(READ "${INPUT}" CONTENT)

get_filename_component(OUTPUT_DIR "${OUTPUT}" DIRECTORY)
get_filename_component(NAME "${OUTPUT}" NAME_WE)

file(MAKE_DIRECTORY "${OUTPUT_DIR}")

file(WRITE "${OUTPUT}"
"static constexpr char ${NAME}[] = R\"GLSL(
${CONTENT}
)GLSL\";
")
