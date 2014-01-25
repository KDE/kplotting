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

target_include_directories(KF5Plotting INTERFACE "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/KPlotting>")

target_link_libraries(KF5Plotting PUBLIC Qt5::Widgets)

set_target_properties(KF5Plotting PROPERTIES VERSION   ${KPLOTTING_VERSION_STRING}
                                             SOVERSION ${KPLOTTING_SOVERSION}
                                             EXPORT_NAME Plotting
)

ecm_generate_headers(
  KPlotAxis
  KPlotPoint
  KPlotObject
  KPlotWidget

  MODULE_NAME KPlotting
  REQUIRED_HEADERS KPlotting_HEADERS
)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/KPlotting DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel)

install(TARGETS KF5Plotting EXPORT KF5PlottingTargets ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kplotting_export.h
  ${KPlotting_HEADERS}
  DESTINATION ${INCLUDE_INSTALL_DIR}/KPlotting COMPONENT Devel
)


include(ECMGeneratePriFile)
ecm_generate_pri_file(BASE_NAME KPlotting LIB_NAME KF5Plotting DEPS "widgets" FILENAME_VAR PRI_FILENAME)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
