
find_package(Qt6 COMPONENTS Gui Quick)

qt_add_executable(ProcessManagerApplication
    main.cpp
)

qt_add_qml_module(ProcessManagerApplication
    URI ProcessManager
    VERSION 1.0
    NO_PLUGIN
    QML_FILES
        Main.qml
        ProcessView.qml
    SOURCES
        foreignprocesslistmodel.h
        foreignprocessmanager.h
        foreignprocessmodel.h
)

add_custom_command(TARGET ProcessManagerApplication POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_LIST_DIR}/settings.ini
        $<TARGET_FILE_DIR:ProcessManagerApplication>
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
        Qt::Quick

)

include(GNUInstallDirs)
install(TARGETS ProcessManagerApplication
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
