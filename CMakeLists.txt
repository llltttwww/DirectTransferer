cmake_minimum_required(VERSION 3.5)

project(DirectTransfer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

include_directories("${CMAKE_CURRENT_LIST_DIR}\\external_libs\\pocketsphinx\\include")
# link_libraries("E:\\Qt projects\\DirectTransfer\\external_libs\\pocketsphinx\\build\\Debug\\pocketsphinx.lib")




set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        resources/icon.rc
)

set(ICON_SOURCES ${CMAKE_CURRENT_LIST_DIR}\\resources\\icon.ico)





if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DirectTransfer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        external_functions.h
        external_functions.cpp
        sub_thread.h
        sub_thread.cpp
        tdialoglogin.h tdialoglogin.cpp tdialoglogin.ui

        resources/icon.ico resources/image.jpg
        res.qrc

        res.qrc
        res.qrc

    )











# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DirectTransfer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DirectTransfer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DirectTransfer
            ${PROJECT_SOURCES}
        )
    endif()
endif()


# find_library(MY_LIBRARY NAMES pocketsphinx HINTS E:\\Qt projects\\DirectTransfer\\external_libs\\pocketsphinx\\build\\Debug\\pocketsphinx.lib)

link_directories("${CMAKE_CURRENT_LIST_DIR}\\external_libs\\pocketsphinx\\build\\Debug")

target_link_libraries(DirectTransfer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries( DirectTransfer PRIVATE "${CMAKE_CURRENT_LIST_DIR}\\external_libs\\pocketsphinx\\build\\Debug\\pocketsphinx.lib")
target_link_libraries(DirectTransfer PRIVATE Qt6::Multimedia)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DirectTransfer)
endif()
set_target_properties(DirectTransfer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DirectTransfer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DirectTransfer)
endif()
