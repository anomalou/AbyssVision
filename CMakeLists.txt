cmake_minimum_required(VERSION 3.0.0)
project(Medium VERSION 0.1.0)

include(CTest)

set(PROJECT_DIR "C:/Projects/Medium")  #set full path here

file(GLOB_RECURSE SOURCES ${PROJECT_DIR}/include/*.h ${PROJECT_DIR}/src/*.cpp)

set(SDL2_INCLUDE_DIR ${PROJECT_DIR}/sdl/include/SDL2)
set(SDL2TTF_INCLUDE_DIR ${PROJECT_DIR}/sdl_ttf/include/SDL2)
set(SDL2IMG_INCLUDE_DIR ${PROJECT_DIR}/sdl_image/include/SDL2)
set(GLM_INCLUDE_DIR ${PROJECT_DIR}/glm)
set(SDL2_LIBRARY_DIR ${PROJECT_DIR}/sdl/lib)
set(SDL2TTF_LIBRARY_DIR ${PROJECT_DIR}/sdl_ttf/lib)
set(SDL2IMG_LIBRARY_DIR ${PROJECT_DIR}/sdl_image/lib)

add_executable(Medium ${SOURCES})

target_include_directories(Medium PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(Medium PUBLIC ${SDL2TTF_INCLUDE_DIR})
target_include_directories(Medium PUBLIC ${SDL2IMG_INCLUDE_DIR})
target_include_directories(Medium PUBLIC ${GLM_INCLUDE_DIR})
target_include_directories(Medium PUBLIC ${PROJECT_DIR}/include)
target_link_libraries(Medium -lmingw32 -lopengl32 -lglu32 ${SDL2_LIBRARY_DIR}/libSDL2main.a ${SDL2_LIBRARY_DIR}/libSDL2.dll.a ${SDL2TTF_LIBRARY_DIR}/libSDL2_ttf.dll.a ${SDL2IMG_LIBRARY_DIR}/libSDL2_image.dll.a -mwindows -mconsole)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)