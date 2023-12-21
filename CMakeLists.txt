cmake_minimum_required(VERSION 3.26)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

project(RenderEngine)

set(TargetName RenderEngine)
set(ImGuiDir ThirdParty/imgui/)
set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

file (GLOB_RECURSE ResFiles Resource/*.rc)
file (GLOB_RECURSE SrcFiles Src/*.cpp)
file (GLOB_RECURSE ManifestFiles Manifest/*.manifest)

add_executable(${TargetName}
        ${SrcFiles}
        ${ResFiles}
        ${ManifestFiles}
        ${ImGuiDir}/backends/imgui_impl_dx11.cpp
        ${ImGuiDir}/backends/imgui_impl_opengl3.cpp
        ${ImGuiDir}/backends/imgui_impl_win32.cpp
        ${ImGuiDir}/imgui.cpp
        ${ImGuiDir}/imgui_draw.cpp
        ${ImGuiDir}/imgui_tables.cpp
        ${ImGuiDir}/imgui_widgets.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(${TargetName} PRIVATE ENABLE_CONSOLE_LOG)
    target_compile_definitions(${TargetName} PRIVATE BUILD_DEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(${TargetName} PRIVATE BUILD_RELEASE)
endif()

set_target_properties(${TargetName} PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
)

set_target_properties(${TargetName} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION TRUE
)

target_include_directories(${TargetName}
        PRIVATE
        Src/ # self root
        ThirdParty/ # eigen
        ${ImGuiDir}   # imgui
        ${ImGuiDir}/backends # imgui backend
)

find_library(D3D11_LIBRARY d3d11.lib
        PATHS
        "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/"
)

target_link_libraries(${TargetName}
        ${OPENGL_LIBRARIES} # opengl import lib -> Windows Kits\10\Lib\10.0.xxx.0\um\x64\OpenGL32.Lib
        d3d11.lib # d3d
)

# copy assets folder -> use python to do this
# add_custom_command(
#         TARGET ${TargetName} PRE_BUILD
#         COMMAND ${CMAKE_COMMAND}
#         -E copy_directory
#         ${CMAKE_CURRENT_SOURCE_DIR}/Assets
#         ${CMAKE_CURRENT_BINARY_DIR}/Assets
# )