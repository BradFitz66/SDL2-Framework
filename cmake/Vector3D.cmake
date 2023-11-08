set(VECTOR3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/Vector3D)
file(GLOB VECTOR3_SOURCE ${VECTOR3_INCLUDE_DIR}/*.h)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

include_directories(
    ${VECTOR3_INCLUDE_DIR}
)    
    
