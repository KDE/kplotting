cmake_minimum_required(VERSION 2.8.12)

project(KPlotting)

find_package(ECM 1.3.0 REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings)
include(KDECMakeSettings)

set(REQUIRED_QT_VERSION 5.2.0)
find_package(Qt5Widgets ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)

include(FeatureSummary)
include(GenerateExportHeader)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(ECMGenerateHeaders)

set(KF5_VERSION "5.3.0") # handled by release scripts

ecm_setup_version(${KF5_VERSION} VARIABLE_PREFIX KPLOTTING
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kplotting_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PlottingConfigVersion.cmake"
                        SOVERSION 5)


add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(autotests)

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5Plotting")

ecm_configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/KF5PlottingConfig.cmake.in"
                              "${CMAKE_CURRENT_BINARY_DIR}/KF5PlottingConfig.cmake"
                              INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
                              )

install(FILES  "${CMAKE_CURRENT_BINARY_DIR}/KF5PlottingConfig.cmake"
               "${CMAKE_CURRENT_BINARY_DIR}/KF5PlottingConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel )

install(EXPORT KF5PlottingTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5PlottingTargets.cmake NAMESPACE KF5:: )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kplotting_version.h
        DESTINATION ${KF5_INCLUDE_INSTALL_DIR} COMPONENT Devel )

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
   feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
endif()
