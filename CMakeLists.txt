cmake_minimum_required (VERSION 2.8.2)
set (CMAKE_VERBOSE_MAKEFILE TRUE)

project (MinVR_glfw)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${${PROJECT_NAME}_SOURCE_DIR}/build/install" CACHE PATH "default install path" FORCE )
endif()

set (SOURCEFILES 
  main.cpp
  src/GlfwInputDevice.cpp
  src/GlfwPlugin.cpp
  src/GlfwTimer.cpp
  src/GlfwWindow.cpp
  src/GlfwWindowFactory.cpp
)

set (HEADERFILES
  src/GlfwInputDevice.h
  src/GlfwTimer.h
  src/GlfwWindow.h
  src/GlfwWindowFactory.h
)

source_group("Header Files" FILES ${HEADERFILES})

#------------------------------------------
# Download dependencies
#------------------------------------------

set(glfw_checkout_Dir ${CMAKE_SOURCE_DIR}/deps/glfw)
make_directory(${glfw_checkout_Dir})
include(ExternalProject)

set(glfw_PREFIX "${glfw_checkout_Dir}")
set(glfw_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/glfw")

set(glfw_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${glfw_INSTALL_DIR} -DUSE_MSVC_RUNTIME_LIBRARY_DLL=ON -DGLFW_BUILD_DOCS=OFF -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
set(glfw_DIR "${glfw_INSTALL_DIR}")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(glfw_CMAKE_ARGS ${glfw_CMAKE_ARGS} -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD="c++11" -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY="libc++")
endif()

set(glfw_build_dir ${CMAKE_BINARY_DIR}/glfw)
set(glfw_stamp_dir ${glfw_build_dir}/stamp)
set(glfw_tmp_dir ${glfw_build_dir}/tmp)
   
ExternalProject_add(glfw
		PREFIX ${glfw_PREFIX}
		GIT_REPOSITORY https://github.com/ivlab/glfw.git
		GIT_TAG gpu-affinity
		INSTALL_DIR ${glfw_INSTALL_DIR}
		CMAKE_ARGS ${glfw_CMAKE_ARGS}
		UPDATE_COMMAND ""
		DOWNLOAD_DIR ${glfw_checkout_Dir}
		SOURCE_DIR ${glfw_checkout_Dir}
		TMP_DIR ${glfw_tmp_dir}
		STAMP_DIR ${glfw_stamp_dir}
		BINARY_DIR ${glfw_build_dir}
)
 
set_property(TARGET glfw PROPERTY FOLDER "Dependencies")

set(GLFW_INCLUDE_DIR ${glfw_INSTALL_DIR}/include CACHE INTERNAL "Directory of GLFW header files")
if(MSVC)
	set(GLFW_LIBRARY ${glfw_INSTALL_DIR}/lib/glfw3.lib CACHE INTERNAL "GLFW lib file")
else()
	set(GLFW_LIBRARY ${glfw_INSTALL_DIR}/lib/libglfw3.a CACHE INTERNAL "GLFW lib file")
endif()	
include_directories(${GLFW_INCLUDE_DIR})

# OpenGL
find_package(OpenGL REQUIRED)
set(OPENGL_LIBRARIES ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
set(OPENGL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIRS})

#------------------------------------------
# MinVR Dependencies
#------------------------------------------

if (NOT MinVR_INCLUDE_DIRS)
	message( FATAL_ERROR "MinVR_INCLUDE_DIRS must be set." )
endif()
if (NOT MinVR_BINARY_DIRS)
	message( FATAL_ERROR "MinVR_BINARY_DIRS must be set." )
endif()

include_directories(${MinVR_INCLUDE_DIRS})
link_directories(${MinVR_BINARY_DIRS})

#------------------------------------------
# Include Directories
#------------------------------------------

# Include Directories
include_directories (
  src
)

#------------------------------------------
# Specific preprocessor defines
#------------------------------------------

# Windows Section #
if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${WINDOWS_BINARIES} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	find_library(COCOA_LIB Cocoa)
	find_library(IOKIT_LIB IOKit)
	find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    	find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
	set(LIBS_ALL ${LIBS_ALL} ${COCOA_LIB} ${IOKIT_LIB} ${CORE_FOUNDATION_FRAMEWORK} ${CORE_VIDEO_FRAMEWORK})
	message(STATUS "${CORE_VIDEO_FRAMEWORK}")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	find_package(Threads)
	find_package(X11)
	set(LIBS_ALL ${LIBS_ALL} ${CMAKE_THREAD_LIBS_INIT} rt Xrandr Xxf86vm Xi m dl ${X11_LIBRARIES})
endif()

#------------------------------------------
# Set output directories to lib, and bin
#------------------------------------------

make_directory(${CMAKE_BINARY_DIR}/lib)
make_directory(${CMAKE_BINARY_DIR}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
foreach (CONF ${CMAKE_CONFIGURATION_TYPES})
	string (TOUPPER ${CONF} CONF)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/bin)
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/lib)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/lib)
endforeach(CONF CMAKE_CONFIGURATION_TYPES)

set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_RELEASE_POSTFIX "")
set(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
set(CMAKE_MINSIZEREL_POSTFIX "s")

#set the build postfix extension according to the current configuration
if (CMAKE_BUILD_TYPE MATCHES "Release")
	set(CMAKE_BUILD_POSTFIX "${CMAKE_RELEASE_POSTFIX}")
elseif (CMAKE_BUILD_TYPE MATCHES "MinSizeRel")
	set(CMAKE_BUILD_POSTFIX "${CMAKE_MINSIZEREL_POSTFIX}")
elseif (CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
	set(CMAKE_BUILD_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}")
elseif (CMAKE_BUILD_TYPE MATCHES "Debug")
	set(CMAKE_BUILD_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
else()
	set(CMAKE_BUILD_POSTFIX "")
endif()

#------------------------------------------
# Build Target
#------------------------------------------

add_executable ( GLFW_App ${HEADERFILES} ${SOURCEFILES} )
target_link_libraries(GLFW_App ${GLFW_LIBRARY} ${OPENGL_LIBRARIES} debug VRPlugind optimized VRPlugin debug VRIndexd optimized VRIndex ${LIBS_ALL})
add_dependencies( GLFW_App glfw)

add_definitions(-DPLUGINPATH="${CMAKE_INSTALL_PREFIX}/..")
add_executable ( test_glfw test/test.cpp )
target_link_libraries(test_glfw ${OPENGL_LIBRARIES} debug VRPlugind optimized VRPlugin debug VRIndexd optimized VRIndex ${LIBS_ALL})

SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/lib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_library ( ${PROJECT_NAME} SHARED ${HEADERFILES} ${SOURCEFILES} )
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY} ${OPENGL_LIBRARIES} debug VRPlugind optimized VRPlugin debug VRIndexd optimized VRIndex ${LIBS_ALL})
add_dependencies( ${PROJECT_NAME} glfw)

#------------------------------------------
# Install Target
#------------------------------------------

install( TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
         RUNTIME DESTINATION bin)