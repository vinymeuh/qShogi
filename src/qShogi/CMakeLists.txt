set(HEADER_FILES
    BoardModel.h
    GameController.h
    GameLogModel.h
    NorthHandModel.h
    SouthHandModel.h
)

set(SOURCE_FILES
    main.cpp
    BoardModel.cpp
    GameController.cpp
    GameLogModel.cpp
    NorthHandModel.cpp
    SouthHandModel.cpp
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_SKIP_BUILD_RPATH TRUE)

find_package(Qt6 REQUIRED COMPONENTS Core Quick QuickControls2)

qt_add_executable(
    qShogi
    ${HEADER_FILES}
    ${SOURCE_FILES}
    resources/resources.qrc
)

target_link_libraries(
    qShogi
    PRIVATE Qt6::Core Qt6::Quick Qt6::QuickControls2 shogi
)

target_compile_definitions(
    qShogi
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
