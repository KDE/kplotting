add_library(KF6Plotting)
add_library(KF6::Plotting ALIAS KF6Plotting)

target_sources(KF6Plotting PRIVATE
 kplotaxis.cpp
 kplotpoint.cpp
 kplotobject.cpp
 kplotwidget.cpp
)

generate_export_header(KF6Plotting BASE_NAME KPlotting)

target_include_directories(KF6Plotting INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/KPlotting>")

target_link_libraries(KF6Plotting PUBLIC Qt6::Widgets)

set_target_properties(KF6Plotting PROPERTIES VERSION   ${KPLOTTING_VERSION}
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

install(TARGETS KF6Plotting EXPORT KF6PlottingTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kplotting_export.h
  ${KPlotting_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KPlotting COMPONENT Devel
)

if (BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

if(BUILD_QCH)
    ecm_add_qch(
        KF6Plotting_QCH
        NAME KPlotting
        BASE_NAME KF6Plotting
        VERSION ${KF_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${KPlotting_HEADERS}
        MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        LINK_QCHS
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            KPLOTTING_EXPORT
            KPLOTTING_DEPRECATED
            KPLOTTING_DEPRECATED_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()


include(ECMGeneratePriFile)
ecm_generate_pri_file(BASE_NAME KPlotting LIB_NAME KF6Plotting DEPS "widgets" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/KPlotting)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
