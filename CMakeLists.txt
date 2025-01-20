cmake_minimum_required(VERSION 3.16)

project(dictionary VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)
find_package(loglib REQUIRED)
find_package(ICU 7.3 COMPONENTS uc REQUIRED)
find_package(SettingsLib)

set(SOURCES src/dictionaryindex.cpp
            src/dictionary.cpp
            src/utils.cpp
            src/entry.cpp
            src/entrymodel.cpp
        )

set(HEADERS include/dictionaryindex.h
            include/utils.h
            include/dictionary.h
            include/entry.h
            include/entrymodel.h
        )

qt_add_executable(appdictionary
    ${HEADERS}
    ${SOURCES}
    src/main.cpp
)

qt_add_qml_module(appdictionary
    URI dictionary
    VERSION 1.0
    QML_FILES qml/Main.qml
    QML_FILES qml/EntryDelegate.qml)

target_link_libraries(appdictionary
    PRIVATE Qt6::Quick loglib ICU::uc SettingsLib
)

target_include_directories(appdictionary PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(GNUInstallDirs)
install(TARGETS appdictionary
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
