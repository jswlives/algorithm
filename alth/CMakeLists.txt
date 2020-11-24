
set(unit_srcs "")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} unit_srcs)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/structers unit_srcs)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sort unit_srcs)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/search unit_srcs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/structers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sort)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/search)

add_executable(alth ${unit_srcs})