include(ECMAddQtDesignerPlugin)

ecm_qtdesignerplugin_widget(KPlotWidget
    TOOLTIP "A plot widget"
    WHATSTHIS "A widget for easily making 2-dimensional plots"
    GROUP "Plot (KF5)"
)

ecm_add_qtdesignerplugin(kplottingwidgets
    NAME KPlottingWidgets
    OUTPUT_NAME kplotting5widgets
    WIDGETS
        KPlotWidget
    LINK_LIBRARIES
        KF5::Plotting
    INSTALL_DESTINATION "${KDE_INSTALL_QTPLUGINDIR}/designer"
    COMPONENT Devel
)
