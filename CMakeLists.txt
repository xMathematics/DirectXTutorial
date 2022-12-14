cmake_minimum_required (VERSION 3.14)

# ------------------------------------------------------------------------------
# 用户配置
# ------------------------------------------------------------------------------
# 设置解决方案名
project("DirectXTutorial")
# 设置项目名(不能有空格)
set(TARGET_NAME "DirectXTutorial")
# 设置HLSL文件的存放位置
set(HLSL_DIR "HLSL")
# Win7系统设置为ON
set(WIN7_SYSTEM OFF)
# 如果需要编译期编译着色器，设置为ON
# 要求着色器命名格式为：ShaderName_ShaderType.hlsl
# ShaderType为右边任意一种：VS, vs, HS, hs, DS, ds, GS, gs, PS, ps, CS, cs
set(SHADER_STATIC_COMPILE OFF)
# 使用ImGui时设置为ON
# 需要将项目中的ImGui文件夹复制进来，保留*.h/*.cpp/CMakeLists.txt
set(USE_IMGUI OFF)
# 使用Assimp时设置为ON
# 需要将解压的assimp文件夹内CMakeList.txt所在的全部文件复制到当前项目的Assimp文件夹内
set(USE_ASSIMP OFF)

# ------------------------------------------------------------------------------
# 项目细节配置(需熟悉CMake)
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(UNICODE _UNICODE)
if (${WIN7_SYSTEM})
    add_compile_definitions(_WIN32_WINNT=0x601)
endif()

include_directories(src/Header DirectXMath/Inc DirectXSDK/Include)
link_directories(DirectXSDK/Lib/x64)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
file(COPY ${HLSL_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(GLOB HLSL_FILES ${HLSL_DIR}/*.hlsl)
file(GLOB HEADER_FILES ./src/Header/*.h)

aux_source_directory(. DIR_SRCS)

add_executable(
        ${TARGET_NAME}
        WIN32
        ${DIR_SRCS}
        ${HEADER_FILES}

        src/Header/d3dApp.h
        src/Header/d3dUtil.h
        src/Header/DXTrace.h
        src/Header/GameApp.h
        src/Header/GameTimer.h
        src/Header/CpuTimer.h
        src/Header/WinMin.h

        src/Sources/d3dApp.cpp
        src/Sources/d3dUtil.cpp
        src/Sources/DXTrace.cpp
        src/Sources/GameApp.cpp
        src/Sources/GameTimer.cpp
        src/Sources/Main.cpp
        src/Sources/CpuTimer.cpp
)

target_link_libraries(
        ${TARGET_NAME}
        lib/d3d11.lib
        lib/d3dx11.lib
        lib/d3dx11d.lib
        lib/dxgi.lib
        lib/dxguid.lib
        lib/d3dcompiler.lib
        lib/winmm.lib
        lib/d2d1.lib
        lib/dwrite.lib
)
source_group("HLSL Files" FILES ${HLSL_FILES})
file(COPY ${HLSL_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# 输出文件名
set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${TARGET_NAME})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

#if (${SHADER_STATIC_COMPILE})
#    target_sources(${TARGET_NAME} PRIVATE ${HLSL_FILES})
#    file(GLOB HLSL_FILES ${HLSL_DIR}/*.hlsl)
#    foreach(HLSL_FILE ${HLSL_FILES})
#        get_filename_component(HLSL_FDIR ${HLSL_FILE} DIRECTORY)
#        get_filename_component(HLSL_FBASENAME_WE ${HLSL_FILE} NAME_WE)
#        string(CONCAT HLSL_FNAME_WE ${HLSL_FDIR} / ${HLSL_FBASENAME_WE})
#        string(LENGTH ${HLSL_FBASENAME_WE} LEN_FNAME_WE)
#        math(EXPR LEN_FNAME_WE "${LEN_FNAME_WE}-2")
#        string(SUBSTRING ${HLSL_FBASENAME_WE} ${LEN_FNAME_WE} 2 ENTRY_POINT)
#        string(TOLOWER ${ENTRY_POINT} SHADER_TYPE)
#        if ("${SHADER_TYPE}" STREQUAL "vs")
#            set(SHADER_TYPE "Vertex")
#        elseif("${SHADER_TYPE}" STREQUAL "hs")
#            set(SHADER_TYPE "Hull")
#        elseif("${SHADER_TYPE}" STREQUAL "ds")
#            set(SHADER_TYPE "Domain")
#        elseif("${SHADER_TYPE}" STREQUAL "gs")
#            set(SHADER_TYPE "Geometry")
#        elseif("${SHADER_TYPE}" STREQUAL "ps")
#            set(SHADER_TYPE "Pixel")
#        elseif("${SHADER_TYPE}" STREQUAL "cs")
#            set(SHADER_TYPE "Compute")
#        endif()
#        set_source_files_properties(${HLSL_FILE} PROPERTIES
#                VS_SHADER_OBJECT_FILE_NAME HLSL/${HLSL_FBASENAME_WE}.cso
#                VS_SHADER_TYPE ${SHADER_TYPE}
#                VS_SHADER_MODEL 5.0
#                VS_SHADER_ENTRYPOINT ${ENTRY_POINT}
#                VS_SHADER_DISABLE_OPTIMIZATIONS $<$<CONFIG:Debug>:true>
#                VS_SHADER_ENABLE_DEBUG $<$<CONFIG:Debug>:true>)
#    endforeach()
#endif()
#
#if (${USE_IMGUI})
#    add_subdirectory(ImGui)
#    target_compile_definitions(${TARGET_NAME} PRIVATE USE_IMGUI)
#    target_link_libraries(${TARGET_NAME} ImGui)
#    file(COPY imgui.ini DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#endif()
#
#if (${USE_ASSIMP})
#    set(ASSIMP_BUILD_ZLIB ON)
#    set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
#    set(ASSIMP_BUILD_TESTS OFF)
#    set(ASSIMP_INSTALL OFF)
#    set(BUILD_SHARED_LIBS OFF)
#    set(ASSIMP_INJECT_DEBUG_POSTFIX OFF)
#    add_subdirectory("assimp")
#    target_link_libraries(${TARGET_NAME} assimp)
#endif()


