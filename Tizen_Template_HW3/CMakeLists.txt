cmake_minimum_required(VERSION 3.3)
project(gles)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_definitions(-DBASIC_TIZEN)
add_definitions(-D__STRTOK_R__)

#set(SBI_SYSROOT C:/tizen-sdk/platforms/mobile-2.3.1/rootstraps/mobile-2.3.1-device.core)
set(SBI_SYSROOT C:/tizen-sdk-2.4/platforms/tizen-2.4/mobile/rootstraps/mobile-2.4-device.core)

set(SDK_PATH C:/tizen-sdk)

include_directories(${SBI_SYSROOT}/usr/include/libxml2)
include_directories(${SBI_SYSROOT}/usr/include)
include_directories(${SBI_SYSROOT}/usr/include/appcore-agent)
include_directories(${SBI_SYSROOT}/usr/include/appfw)
include_directories(${SBI_SYSROOT}/usr/include/attach-panel)
include_directories(${SBI_SYSROOT}/usr/include/badge)
include_directories(${SBI_SYSROOT}/usr/include/base)
include_directories(${SBI_SYSROOT}/usr/include/cairo)
include_directories(${SBI_SYSROOT}/usr/include/calendar-service2)
include_directories(${SBI_SYSROOT}/usr/include/ckm)
include_directories(${SBI_SYSROOT}/usr/include/contacts-svc)
include_directories(${SBI_SYSROOT}/usr/include/content)
include_directories(${SBI_SYSROOT}/usr/include/context-service)
include_directories(${SBI_SYSROOT}/usr/include/dali)
include_directories(${SBI_SYSROOT}/usr/include/dali-toolkit)
include_directories(${SBI_SYSROOT}/usr/include/dbus-1.0)
include_directories(${SBI_SYSROOT}/usr/include/device)
include_directories(${SBI_SYSROOT}/usr/include/dlog)
include_directories(${SBI_SYSROOT}/usr/include/ecore-1)
include_directories(${SBI_SYSROOT}/usr/include/ecore-con-1)
include_directories(${SBI_SYSROOT}/usr/include/ecore-evas-1)
include_directories(${SBI_SYSROOT}/usr/include/ecore-file-1)
include_directories(${SBI_SYSROOT}/usr/include/ecore-imf-1)
include_directories(${SBI_SYSROOT}/usr/include/ecore-imf-evas-1)
include_directories(${SBI_SYSROOT}/usr/include/ecore-input-1)
include_directories(${SBI_SYSROOT}/usr/include/ecore-input-evas-1)
include_directories(${SBI_SYSROOT}/usr/include/ecore-ipc-1)
include_directories(${SBI_SYSROOT}/usr/include/ecore-x-1)
include_directories(${SBI_SYSROOT}/usr/include/e_dbus-1)
include_directories(${SBI_SYSROOT}/usr/include/edje-1)
include_directories(${SBI_SYSROOT}/usr/include/eet-1)
include_directories(${SBI_SYSROOT}/usr/include/efl-1)
include_directories(${SBI_SYSROOT}/usr/include/efl-extension)
include_directories(${SBI_SYSROOT}/usr/include/efreet-1)
include_directories(${SBI_SYSROOT}/usr/include/eina-1)
include_directories(${SBI_SYSROOT}/usr/include/eina-1/eina)
include_directories(${SBI_SYSROOT}/usr/include/eio-1)
include_directories(${SBI_SYSROOT}/usr/include/eldbus-1)
include_directories(${SBI_SYSROOT}/usr/include/elementary-1)
include_directories(${SBI_SYSROOT}/usr/include/embryo-1)
include_directories(${SBI_SYSROOT}/usr/include/eo-1)
include_directories(${SBI_SYSROOT}/usr/include/eom)
include_directories(${SBI_SYSROOT}/usr/include/ethumb-1)
include_directories(${SBI_SYSROOT}/usr/include/ethumb-client-1)
include_directories(${SBI_SYSROOT}/usr/include/evas-1)
include_directories(${SBI_SYSROOT}/usr/include/ewebkit2-0)
include_directories(${SBI_SYSROOT}/usr/include/feedback)
include_directories(${SBI_SYSROOT}/usr/include/fontconfig)
include_directories(${SBI_SYSROOT}/usr/include/freetype2)
include_directories(${SBI_SYSROOT}/usr/include/geofence)
include_directories(${SBI_SYSROOT}/usr/include/gio-unix-2.0)
include_directories(${SBI_SYSROOT}/usr/include/glib-2.0)
include_directories(${SBI_SYSROOT}/usr/include/harfbuzz)
include_directories(${SBI_SYSROOT}/usr/include/json-glib-1.0)
include_directories(${SBI_SYSROOT}/usr/include/location)
include_directories(${SBI_SYSROOT}/usr/include/maps)
include_directories(${SBI_SYSROOT}/usr/include/media)
include_directories(${SBI_SYSROOT}/usr/include/media-content)
include_directories(${SBI_SYSROOT}/usr/include/messaging)
include_directories(${SBI_SYSROOT}/usr/include/metadata-editor)
include_directories(${SBI_SYSROOT}/usr/include/minicontrol)
include_directories(${SBI_SYSROOT}/usr/include/minizip)
include_directories(${SBI_SYSROOT}/usr/include/network)
include_directories(${SBI_SYSROOT}/usr/include/notification)
include_directories(${SBI_SYSROOT}/usr/include/phonenumber-utils)
include_directories(${SBI_SYSROOT}/usr/include/sensor)
include_directories(${SBI_SYSROOT}/usr/include/shortcut)
include_directories(${SBI_SYSROOT}/usr/include/storage)
include_directories(${SBI_SYSROOT}/usr/include/system)
include_directories(${SBI_SYSROOT}/usr/include/telephony)
include_directories(${SBI_SYSROOT}/usr/include/ui)
include_directories(${SBI_SYSROOT}/usr/include/web)
include_directories(${SBI_SYSROOT}/usr/include/widget_service)
include_directories(${SBI_SYSROOT}/usr/include/widget_viewer_evas)
include_directories(${SBI_SYSROOT}/usr/include/wifi-direct)
include_directories(${SBI_SYSROOT}/usr/lib/dbus-1.0/include)
include_directories(${SBI_SYSROOT}/usr/lib/glib-2.0/include)

include_directories(inc)
include_directories(src/common/include)
include_directories(src/sample)

set(SOURCE_FILES
    inc/gles_sample.h
    shared/res/tizen_gles_sample.png
    src/common/include/basic_camera.h
    src/common/include/basic_gl_set.h
    src/common/include/basic_file_loader.h
    src/common/include/basic_log_utils.h
    src/common/include/basic_renderer.h
    src/common/include/basic_shader.h
    src/common/include/basic_texdata.h
    src/common/include/basic_timer.h
    src/common/platform/common/basic_file_loader.cpp
    src/common/platform/tizen/basic_file_loader_tizen.cpp
    src/common/platform/win/basic_file_loader_win.cpp
    src/common/basic_renderer.cpp
    src/common/basic_renderer_30.cpp
    src/common/basic_shader.cpp
    src/common/basic_camera.cpp
    src/common/basic_log_utils.cpp
    src/common/basic_texdata.cpp
    src/common/basic_timer.cpp
    src/sample/texturing_view.cpp
    src/sample/texturing_view.h
    src/sample/vertex_lighting_view.cpp
    src/sample/vertex_lighting_view.h
    src/sample/frag_lighting_view.cpp
    src/sample/frag_lighting_view.h
    src/sample/env_mapping_view.cpp
    src/sample/env_mapping_view.h
    src/sample/normal_mapping_view.cpp
    src/sample/normal_mapping_view.h
    src/sample/launcher_interface.cpp
    src/sample/launcher_interface.h
    src/sample/sample_view.cpp
    src/sample/sample_view.h
    src/sample/sample_launcher.cpp
    src/sample/sample_launcher.h
    src/gles_sample.c
    )

add_executable(gles ${SOURCE_FILES})