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
	mBall.Update(dt);
	mPaddle.Update(dt, mBall);

	BoundaryEdge edge;
	
	if (mPaddle.Bounce(mBall)) {
		return;
	}

	if (mLevelBoundary.HasCollided(mBall, edge)) {
		mBall.Bounce(edge);
		return;
	}

	mLevel.Update(dt, mBall);
}

void Breakout::Draw(Screen& screen) { 	
	mBall.Draw(screen);
	mPaddle.Draw(screen);
	mLevel.Draw(screen);

	screen.Draw(mLevelBoundary.GetAARectangle(), Color::White());
}

const std::string& Breakout::GetName() const {
	static std::string name = "Breakout!";

	return name;
}

void Breakout::ResetGame() {
	Vec2D topLeftPoint = Vec2D(
			App::Singleton().GetWidth() / 2 - Paddle::PADDLE_WIDTH / 2,
			App::Singleton().GetHeight() - 3 * Paddle::PADDLE_HEIGHT);

	AARectangle paddleRect = {topLeftPoint, Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT};
	AARectangle levelBoundary = {
		Vec2D::ZERO, 
		App::Singleton().GetWidth(), 
		App::Singleton().GetHeight()
	};

	mLevelBoundary = {levelBoundary};
	
	mPaddle.Init(paddleRect, levelBoundary);

	mBall.MoveTo(Vec2D(App::Singleton().GetWidth() / 2, App::Singleton().GetHeight() / 2));
	mBall.SetVelocity(INITIAL_BALL_VELOCITY);

	mLevel.Init(levelBoundary);
}
