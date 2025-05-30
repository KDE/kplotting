add_library(KF6Plotting)
add_library(KF6::Plotting ALIAS KF6Plotting)

set_target_properties(KF6Plotting PROPERTIES
    VERSION     ${KPLOTTING_VERSION}
    SOVERSION   ${KPLOTTING_SOVERSION}
    EXPORT_NAME Plotting
)

target_sources(KF6Plotting PRIVATE
  kplotaxis.cpp
  kplotpoint.cpp
  kplotobject.cpp
  kplotwidget.cpp
)

ecm_generate_export_header(KF6Plotting
    BASE_NAME KPlotting
    GROUP_BASE_NAME KF
    VERSION ${KF_VERSION}
    USE_VERSION_HEADER
    DEPRECATED_BASE_VERSION 0
)

target_include_directories(KF6Plotting INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/KPlotting>")

target_link_libraries(KF6Plotting PUBLIC Qt6::Widgets)

ecm_generate_headers(KPlotting_HEADERS
  HEADER_NAMES
  KPlotAxis
  KPlotPoint
  KPlotObject
  KPlotWidget

  REQUIRED_HEADERS KPlotting_HEADERS
)

ecm_generate_qdoc(KF6Plotting kplotting.qdocconf)

install(TARGETS KF6Plotting EXPORT KF6PlottingTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kplotting_export.h
  ${KPlotting_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KPlotting COMPONENT Devel
)

if(BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()
