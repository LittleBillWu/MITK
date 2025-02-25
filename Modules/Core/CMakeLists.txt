set(TOOL_CPPS "")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.1)
  set(optional_public_target_depends stdc++fs)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
  set(optional_public_target_depends c++fs)
endif()

mitk_create_module(
  INCLUDE_DIRS
    PUBLIC
      ${MITK_BINARY_DIR}
    PRIVATE
      src/Algorithms
      src/Controllers
      src/DataManagement
      src/Interactions
      src/IO
      src/Rendering
  PCH
    mitkBaseRenderer.h
    mitkImage.h
  DEPENDS
    PUBLIC
      MitkLog
      CppMicroServices
  PACKAGE_DEPENDS
    PUBLIC
      Boost
      nlohmann_json
      ITK|IOImageBase+SpatialObjects+Statistics
      #ITK|Statistics+Transform
      VTK|FiltersTexture+FiltersParallel+ImagingStencil+ImagingMath+InteractionStyle+RenderingOpenGL2+RenderingVolumeOpenGL2+RenderingFreeType+RenderingLabel+InteractionWidgets+IOGeometry+IOImage+IOXML
    PRIVATE
      ITK|IOBioRad+IOBMP+IOBruker+IOCSV+IOGDCM+IOGE+IOGIPL+IOHDF5+IOIPL+IOJPEG+IOJPEG2000+IOLSM+IOMesh+IOMeta+IOMINC+IOMRC+IONIFTI+IONRRD+IOPNG+IOSiemens+IOSpatialObjects+IOStimulate+IOTIFF+IOTransformBase+IOTransformHDF5+IOTransformInsightLegacy+IOTransformMatlab+IOVTK+IOXML
      tinyxml2
      ${optional_private_package_depends}
  TARGET_DEPENDS
    PUBLIC
      ${optional_public_target_depends}
  # Do not automatically create CppMicroServices initialization code.
  # Because the VTK "auto-init" functionality injects file-local static
  # initialization code in every cpp file which includes a VTK header,
  # static initialization order becomes an issue again. For the Mitk
  # core library, we need to ensure that the VTK static initialization stuff
  # happens before the CppMicroServices initialization, since the latter
  # might already use VTK code which needs to access VTK object factories.
  # Hence, CppMicroServices initialization code is placed manually within
  # the mitkCoreActivator.cpp file.
  NO_INIT
)
if(NOT TARGET ${MODULE_TARGET})
  message(SEND_ERROR "Core target ${MODULE_TARGET} does not exist")
endif()

function(_itk_create_factory_register_manager)
  # In MITK_ITK_Config.cmake, we do *not* include ITK_USE_FILE, which
  # prevents multiple registrations/unregistrations of ITK IO factories
  # during library loading/unloading (of MITK libraries). However, we need
  # "one" place where the IO factories are registered at
  # least once. This could be the application executable, but every executable would
  # need to take care of that itself. Instead, we allow the auto registration in the
  # Mitk Core library.
  set(NO_DIRECTORY_SCOPED_ITK_COMPILE_DEFINITION 1)
  find_package(ITK)
  include(${ITK_USE_FILE})

  if(NOT ITK_NO_IO_FACTORY_REGISTER_MANAGER)
    # We manually add the define which will be of target scope. MITK
    # patches ITK_USE_FILE to remove the directory scoped compile
    # definition since it would be propagated to other targets in the
    # same directory scope but these targets might want to *not*
    # use the ITK factory manager stuff.
    target_compile_definitions(${MODULE_TARGET} PRIVATE ITK_IO_FACTORY_REGISTER_MANAGER)
  endif()
endfunction()
_itk_create_factory_register_manager()

if(BUILD_TESTING)
  add_subdirectory(TestingHelper)
  add_subdirectory(test)
endif()
