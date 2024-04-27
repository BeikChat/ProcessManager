
find_package(Qt6 COMPONENTS Gui Quick)

qt_add_executable(ProcessManagerApplication
    main.cpp
)

qt_add_qml_module(ProcessManagerApplication
    URI ProcessManagerApplication
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES

        SOURCES qmlprocessmanagersingleton.h qmlprocessmanagersingleton.cpp

)

set_target_properties(ProcessManagerApplication PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(ProcessManagerApplication
    PRIVATE
        ProcessManagerCore
        Qt6::Quick

)

include(GNUInstallDirs)
install(TARGETS ProcessManagerApplication
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
