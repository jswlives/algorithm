
set(unit_srcs "")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} unit_srcs)

add_executable(linux ${unit_srcs})