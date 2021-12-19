
find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test Widgets)

include(ECMAddTests)

ecm_add_tests(
    kplotpointtest.cpp
    kplotaxistest.cpp
    kplotobjecttest.cpp
    kplotwidgettest.cpp
    LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::Plotting
)
