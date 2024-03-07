cmake_minimum_required(VERSION 3.16)

project(dictionary VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)
find_package(LogLibrary)
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
    PRIVATE Qt6::Quick LogLibrary ICU::uc SettingsLib
)

target_include_directories(appdictionary PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(GNUInstallDirs)
install(TARGETS appdictionary
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

option(enable_test "Compile and run tests" OFF)

if (enable_test)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DTESTING_ENABLED")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTESTING_ENABLED")

    find_package(GTest REQUIRED)

    # there must be a better way to find AnyRPC...
    LIST(APPEND CMAKE_MODULE_PATH ~/git/spix/cmake/modules)

    find_package(Spix REQUIRED)
    enable_testing()


    set(TEST_SOURCES tests/dictionaryindex_test.cpp
                     tests/dictionary_test.cpp
                     tests/misc_test.cpp
                     tests/testutils.h
                     tests/testutils.cpp
                     )

    add_executable(dictionary_test ${HEADERS} ${SOURCES} ${TEST_SOURCES})

    target_link_directories(dictionary_test PRIVATE $ENV{CMAKE_SYSROOT}/usr/lib)
    target_link_libraries(dictionary_test GTest::gtest_main LogLibrary Qt6::Quick ICU::uc SettingsLib)

    target_include_directories(dictionary_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

    # input files for tests
    FILE(COPY tests/files/simple_input_1 DESTINATION ${CMAKE_BINARY_DIR})
    FILE(COPY tests/files/empty_input DESTINATION ${CMAKE_BINARY_DIR})
    FILE(COPY tests/files/unicode_input DESTINATION ${CMAKE_BINARY_DIR})
    FILE(COPY tests/files/simple_input_2 DESTINATION ${CMAKE_BINARY_DIR})
    FILE(COPY tests/files/de_dict_sample DESTINATION ${CMAKE_BINARY_DIR})
    FILE(COPY tests/files/de_dict_sample_sorted DESTINATION ${CMAKE_BINARY_DIR})


    include(GoogleTest)
    # gtest_discover_tests(mailclient_test)

    install(TARGETS dictionary_test
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
