cmake_minimum_required(VERSION 3.16)

set(KF_VERSION "5.86.0") # handled by release scripts
project(KPlotting VERSION ${KF_VERSION})

include(FeatureSummary)
find_package(ECM 5.86.0  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://commits.kde.org/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)


set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(KDEGitCommitHooks)

set(REQUIRED_QT_VERSION 5.15.2)
find_package(Qt5Widgets ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)


include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMAddQch)

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

option(BUILD_DESIGNERPLUGIN "Build plugin for Qt Designer" ON)
add_feature_info(DESIGNERPLUGIN ${BUILD_DESIGNERPLUGIN} "Build plugin for Qt Designer")

ecm_setup_version(PROJECT VARIABLE_PREFIX KPLOTTING
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kplotting_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PlottingConfigVersion.cmake"
                        SOVERSION 5)
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x050f02)

add_subdirectory(src)
add_subdirectory(examples)
if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5Plotting")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF5Plotting_QCH
        FILE KF5PlottingQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5PlottingQchTargets.cmake\")")
endif()

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/KF5PlottingConfig.cmake.in"
                              "${CMAKE_CURRENT_BINARY_DIR}/KF5PlottingConfig.cmake"
                              INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
                              )

install(FILES  "${CMAKE_CURRENT_BINARY_DIR}/KF5PlottingConfig.cmake"
               "${CMAKE_CURRENT_BINARY_DIR}/KF5PlottingConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel )

install(EXPORT KF5PlottingTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5PlottingTargets.cmake NAMESPACE KF5:: )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kplotting_version.h
        DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
