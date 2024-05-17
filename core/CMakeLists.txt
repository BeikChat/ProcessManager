
qt_add_library(ProcessManagerCore STATIC
    processlistmodel.h processlistmodel.cpp
    processmodel.h processmodel.cpp
    processmanager.h processmanager.cpp
)

target_link_libraries(ProcessManagerCore PRIVATE Qt::Core)

target_include_directories(ProcessManagerCore
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
