cmake_minimum_required(VERSION 3.16)

project(MarchingSquares)

set(CMAKE_CXX_STANDARD 17)

# Get all the source files
file(GLOB_RECURSE SOURCES src/*.cpp)
include_directories(headers /usr/include)
add_executable(${PROJECT_NAME} ${SOURCES})

#------------------------------------------------------------------------------------
# Add dependencies here
#------------------------------------------------------------------------------------

# find_package(SFML 2.5 COMPONENTS graphics QUIET)
# if(NOT SFML_FOUND)
#     message(STATUS ">>> Installing SFML because it wasn't found")

#     message(WARNING "Attempting to build SFML from source. If this fails, you may be missing system dependencies.\n\
# On Ubuntu/Debian, try installing the following packages:\n\n\
#   sudo apt install libx11-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev \\\n\
#   libgl1-mesa-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libogg-dev\n\n\
# These packages provide X11, OpenGL, input, audio, and codec development files required by SFML.")


#     include(FetchContent)
#     FetchContent_Declare(SFML
#         GIT_REPOSITORY https://github.com/SFML/SFML.git
#         GIT_TAG 2.6.x
#     )
#     FetchContent_MakeAvailable(SFML)
# endif()

find_package(SFML 2.5 COMPONENTS graphics QUIET)
if(NOT SFML_FOUND)
    if(BUILD_SFML_FROM_SOURCE)
        message(STATUS ">>> Installing SFML because it wasn't found")

        message(WARNING
            "Attempting to build SFML from source. If this fails, you may be missing system dependencies.\n\
            On Ubuntu/Debian, try installing the following packages:\n\n\
            sudo apt install -y \
            libfreetype-dev libx11-dev libxrandr-dev \\\n\
            libxcursor-dev libxi-dev libudev-dev \\\n\
            libgl-dev libflac-dev libogg-dev \\\n\
            libvorbis-dev libvorbisenc2 libvorbisfile3 \\\n\
            libpthread-stubs0-dev \n\n\
            These packages provide FreeType, X11, OpenGL, audio codecs, threading, and input device development files required by SFML."
            )

        include(FetchContent)
        FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x
        )
        FetchContent_MakeAvailable(SFML)
    else()
        message(FATAL_ERROR "SFML not found. Run bash ./Build.sh --sfml-src to build it from source or install SFML manually.")
    endif()
endif()

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

#------------------------------------------------------------------------------------

# Create a custom target to copy the assets
set(COPY_ASSETS_TARGET "copy_assets_${PROJECT_NAME}")

add_custom_target(${COPY_ASSETS_TARGET} ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets/${PROJECT_NAME}
    COMMENT "Copying assets for ${PROJECT_NAME} to the build directory"
)

add_dependencies(${PROJECT_NAME} ${COPY_ASSETS_TARGET})

#------------------------------------------------------------------------------------

# Define the path to the assets folder
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    ASSETS_PATH="${CMAKE_BINARY_DIR}/assets/${PROJECT_NAME}")

