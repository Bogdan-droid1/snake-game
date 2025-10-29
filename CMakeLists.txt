cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)



set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization

if(MSVC) 
add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
endif()

project(mygame)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)


add_subdirectory(thirdparty/glfw-3.3.2)			#window oppener
add_subdirectory(thirdparty/glad)				#opengl loader
add_subdirectory(thirdparty/glm)				#math
add_subdirectory(thirdparty/stb_image)


# DON'T ADD THE SOURCES BY HAND, they are already added with this macro
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/cppfiles/*.cpp")


add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)


target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC GLFW_INCLUDE_NONE=1) 

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC SHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders/")



target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES}    
"src/headerfiles/GameClass.h" "src/cppfiles/GameClass.cpp"
"src/headerfiles/RendererClass.h" "src/cppfiles/RendererClass.cpp"
"src/headerfiles/ShaderClass.h" "src/cppfiles/ShaderClass.cpp"
"src/headerfiles/TextureClass.h" "src/cppfiles/TextureClass.cpp")


if(MSVC)

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

	#add this line if you want to remove the console!
	#set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console

endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")


target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw glad stb_image)
