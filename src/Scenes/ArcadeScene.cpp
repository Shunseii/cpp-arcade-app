#include "Scenes/ArcadeScene.h"

#include <iostream>
#include "Graphics/Screen.h"
#include "Shapes/Line2D.h"
#include "Shapes/Triangle.h"
#include "Shapes/AARectangle.h"
#include "Shapes/Circle.h"
#include "Graphics/Color.h"
#include "Input/GameController.h"

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game) {
	switch (game) {
		case TETRIS: 
			break;
		case BREAK_OUT:
			break;
		case ASTEROIDS:
			break;
		case PACMAN:
			break;
		default: 
		   	break;
	}

	return nullptr;
}

ArcadeScene::ArcadeScene() {}

void ArcadeScene::Init() {
	ButtonAction action;
	action.key = GameController::ActionKey();
	action.action = [](uint32_t dt, InputState state){
		if (GameController::IsPressed(state)) {
			std::cout << "Action button was pressed." << std::endl;
		}
	};

	mGameController.AddInputAction(action);
}

void ArcadeScene::Update(uint32_t dt) {}

void ArcadeScene::Draw(Screen& theScreen) {
	Triangle triangle{Vec2D(theScreen.Width() / 2, 10), Vec2D(10, theScreen.Height() / 2), Vec2D(theScreen.Width() / 2, theScreen.Height() / 2)};
	Circle circle{Vec2D(theScreen.Width() / 2, theScreen.Height() / 2), 50};

	theScreen.Draw(triangle, Color::Blue(), true, Color::Blue());
	theScreen.Draw(circle, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));
}

const std::string& ArcadeScene::GetSceneName() const {
	static std::string sceneName = "Arcade Scene";
	return sceneName;
}
