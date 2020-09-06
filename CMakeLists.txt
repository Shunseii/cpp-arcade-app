cmake_minimum_required(VERSION 3.7)

project (arcade)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} 
	src/Main.cpp 
	src/Utils/Vec2D.cpp 
	src/Utils/Utils.cpp
	src/Graphics/Color.cpp
	src/Graphics/ScreenBuffer.cpp
	src/Graphics/Screen.cpp
	src/Shapes/Line2D.cpp
	src/Shapes/Shape.cpp
	src/Shapes/Triangle.cpp
	src/Shapes/AARectangle.cpp
	src/Shapes/Circle.cpp
	src/App/App.cpp
	src/Scenes/ArcadeScene.cpp
	src/Input/InputController.cpp
	src/Input/GameController.cpp
	src/Scenes/GameScene.cpp
	src/Utils/FileCommandLoader.cpp
	src/Games/Breakout/Breakout.cpp
	src/Games/Breakout/Excluder.cpp
	src/Games/Breakout/Paddle.cpp
	src/Games/Breakout/Ball.cpp
	src/Games/Breakout/LevelBoundary.cpp
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_include_directories(${PROJECT_NAME}
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/include/Graphics
		${PROJECT_SOURCE_DIR}/include/Utils
		${PROJECT_SOURCE_DIR}/include/Shapes
		${PROJECT_SOURCE_DIR}/include/App
		${PROJECT_SOURCE_DIR}/include/Scene
		${PROJECT_SOURCE_DIR}/include/Input
		${PROJECT_SOURCE_DIR}/include/Games
		${PROJECT_SOURCE_DIR}/include/Games/Breakout
)
