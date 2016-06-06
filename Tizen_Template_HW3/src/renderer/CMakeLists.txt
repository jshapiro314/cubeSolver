include_directories(include)

set(common_src
        basic_camera.cpp
        basic_log_utils.cpp
        basic_texdata.cpp
        platform/common/basic_file_loader.cpp
        basic_timer.cpp
        iml_utils.cpp
        basic_shader.cpp
        basic_renderer.cpp
        renderer/iml_renderer_31.cpp
        renderer/iml_renderer_shader.cpp
        platform/win/basic_file_loader_win.cpp
        )

add_library(BasicRenderer STATIC ${common_src})
add_library(FreeImage SHARED IMPORTED)
set_property(TARGET FreeImage PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/bin/FreeImage.dll)
set_property(TARGET FreeImage PROPERTY IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/FreeImage.lib)

target_link_libraries(BasicRenderer
        opengl32
        glu32
        glew32
        FreeImage)