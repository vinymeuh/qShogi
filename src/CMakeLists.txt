set(HEADER_FILES
    include/BoardModel.h
    include/GameController.h
    include/GameMovesModel.h
    include/HandModel.h
)

set(SOURCE_FILES
    src/main.cpp
    src/BoardModel.cpp
    src/GameController.cpp
    src/GameMovesModel.cpp
    src/HandModel.cpp
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
    resources.qrc
)

include_directories(include ../libshogi/include)

target_link_libraries(
    qShogi
    PRIVATE Qt6::Core Qt6::Quick Qt6::QuickControls2 shogi
)

target_compile_definitions(
    qShogi
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
