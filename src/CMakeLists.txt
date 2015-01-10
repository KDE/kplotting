add_definitions(-DQT_NO_CAST_FROM_ASCII)

set(kplotting_SRCS
 kplotaxis.cpp
 kplotpoint.cpp
 kplotobject.cpp
 kplotwidget.cpp
)

add_library(KF5Plotting ${kplotting_SRCS})
generate_export_header(KF5Plotting BASE_NAME KPlotting)
add_library(KF5::Plotting ALIAS KF5Plotting)

target_include_directories(KF5Plotting INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/KPlotting>")

target_link_libraries(KF5Plotting PUBLIC Qt5::Widgets)

set_target_properties(KF5Plotting PROPERTIES VERSION   ${KPLOTTING_VERSION_STRING}
                                             SOVERSION ${KPLOTTING_SOVERSION}
                                             EXPORT_NAME Plotting
)

ecm_generate_headers(KPlotting_HEADERS
  HEADER_NAMES
  KPlotAxis
  KPlotPoint
  KPlotObject
  KPlotWidget

  REQUIRED_HEADERS KPlotting_HEADERS
)

install(TARGETS KF5Plotting EXPORT KF5PlottingTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kplotting_export.h
  ${KPlotting_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KPlotting COMPONENT Devel
)


include(ECMGeneratePriFile)
ecm_generate_pri_file(BASE_NAME KPlotting LIB_NAME KF5Plotting DEPS "widgets" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/KPlotting)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
