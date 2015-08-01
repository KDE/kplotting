
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test Widgets)

include(ECMAddTests)

ecm_add_tests(
    kplotpointtest.cpp
    kplotaxistest.cpp
    kplotobjecttest.cpp
    kplotwidgettest.cpp
    LINK_LIBRARIES Qt5::Test KF5::Plotting
)
