#include "Games/Breakout/Breakout.h"

#include <iostream>
#include "Input/GameController.h"
#include "App/App.h"

void Breakout::Init(GameController& controller) {
	controller.ClearAll();
	ResetGame();

	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state){
		if (GameController::IsPressed(state)) {
			mPaddle.SetMovementDirection(PaddleDirection::LEFT);
		} else {
			mPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
		}
	};
	controller.AddInputAction(leftKeyAction);
	
	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state){
		if (GameController::IsPressed(state)) {
			mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
		} else {
			mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
		}
	};
	controller.AddInputAction(rightKeyAction);
}

void Breakout::Update(uint32_t dt) {
	mPaddle.Update(dt);
}

void Breakout::Draw(Screen& screen) { 	
	mPaddle.Draw(screen);
}

std::string Breakout::GetName() const {
	return "Breakout";
}

void Breakout::ResetGame() {
	Vec2D topLeftPoint = {
		App::Singleton().GetWidth() / 2 - Paddle::PADDLE_WIDTH / 2,
		App::Singleton().GetHeight() - 3 * Paddle::PADDLE_HEIGHT
	};

	AARectangle paddleRect = {topLeftPoint, Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT};
	AARectangle levelBoundary = {
		Vec2D::ZERO, 
		App::Singleton().GetWidth(), 
		App::Singleton().GetHeight()
	};

	mPaddle.Init(paddleRect, levelBoundary);
}
