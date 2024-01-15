if(WIN32 OR APPLE OR (DEFINED OpenGL_GL_PREFERENCE AND OpenGL_GL_PREFERENCE STREQUAL LEGACY))
  find_package(OpenGL REQUIRED)
  list(APPEND ALL_LIBRARIES OpenGL::GL)
else()
  find_package(OpenGL REQUIRED OPTIONAL_COMPONENTS EGL GLX)
  list(APPEND ALL_LIBRARIES OpenGL::OpenGL)

  if(TARGET OpenGL::EGL)
    list(APPEND ALL_LIBRARIES OpenGL::EGL)
  elseif(TARGET OpenGL::GLX)
    list(APPEND ALL_LIBRARIES OpenGL::GLX)
  else()
    set(OpenGL_GL_PREFERENCE LEGACY)
    find_package(OpenGL REQUIRED)
    list(APPEND ALL_LIBRARIES OpenGL::GL)
  endif()
endif()
