#include "Games/Breakout/Breakout.h"

#include <iostream>
#include "Input/GameController.h"
#include "App/App.h"
#include "Shapes/Circle.h"

void Breakout::Init(GameController& controller) {
	controller.ClearAll();
	mLevels = BreakoutGameLevel::LoadLevelsFromFile(
			App::GetBasePath() + "../src/Assets/BreakoutLevels.txt");
	
	ResetGame();

	ButtonAction serveAction;
	serveAction.key = GameController::ActionKey();
	serveAction.action = [this](uint32_t dt, InputState state) {
		if (mGameState == IN_SERVE) {
			if (GameController::IsPressed(state)) {
				mGameState = IN_PLAY;

				if (mPaddle.IsMovingLeft()) {
					mBall.SetVelocity(Vec2D(-INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
				} else {
					mBall.SetVelocity(Vec2D(INITIAL_BALL_SPEED, INITIAL_BALL_SPEED));
				}
			}
		} else if (mGameState == IN_GAME_OVER) {
			if (GameController::IsPressed(state)) {
				ResetGame();
			}
		}
	};

	controller.AddInputAction(serveAction);

	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state){
		if (mGameState == IN_PLAY || mGameState == IN_SERVE) {
			if (GameController::IsPressed(state)) {
				mPaddle.SetMovementDirection(PaddleDirection::LEFT);
			} else {
				mPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
			}
		}
	};
	controller.AddInputAction(leftKeyAction);
	
	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state){
		if (mGameState == IN_PLAY || mGameState == IN_SERVE) {
			if (GameController::IsPressed(state)) {
				mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
			} else {
				mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
			}
		}
	};
	controller.AddInputAction(rightKeyAction);
}

void Breakout::Update(uint32_t dt) {
	if (mGameState == IN_SERVE) {
		mPaddle.Update(dt, mBall);
		SetToServeState();
	} else if (mGameState == IN_PLAY) {
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

		GetCurrentLevel().Update(dt, mBall);

		if (IsBallPassedCutoffY()) {
			ReduceLifeByOne();

			if (!IsGameOver()) {
				SetToServeState();
			} else {
				mGameState = IN_GAME_OVER;
			}
		} else if (GetCurrentLevel().IsLevelComplete()) {
			mCurrentLevel = (mCurrentLevel + 1) % mLevels.size();
			ResetGame(mCurrentLevel);
		}
	}
}

void Breakout::Draw(Screen& screen) { 	
	mBall.Draw(screen);
	mPaddle.Draw(screen);
	GetCurrentLevel().Draw(screen);

	screen.Draw(mLevelBoundary.GetAARectangle(), Color::White());
	
	Circle lifeCircle = {Vec2D(7, App::Singleton().GetHeight() - 2), 5};

	for (int i = 0; i < mLives; ++i) {
		screen.Draw(lifeCircle, Color::Red(), true, Color::Red());
		lifeCircle.MoveBy(Vec2D(17, 0));
	}
}

const std::string& Breakout::GetName() const {
	static std::string name = "Breakout!";

	return name;
}

void Breakout::ResetGame(size_t toLevel) {
	mYCutoff = App::Singleton().GetHeight() - 2 * Paddle::PADDLE_HEIGHT;
	mLives = NUM_LIVES;
	mCurrentLevel = toLevel;

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

	mBall.MoveTo(Vec2D(App::Singleton().GetWidth() / 2, App::Singleton().GetHeight() * 0.75f));

	SetToServeState();
}

void Breakout::SetToServeState() {
	mGameState = IN_SERVE;
	mBall.Stop();

	mBall.MoveTo(Vec2D(mPaddle.GetAARectangle().GetCenterPoint().GetX(), 
				mPaddle.GetAARectangle().GetTopLeftPoint().GetY() - mBall.GetRadius() - 1));
}

bool Breakout::IsBallPassedCutoffY() const {
	return mBall.GetPosition().GetY() > mYCutoff;
}

void Breakout::ReduceLifeByOne() {
	if (mLives >= 0) {
		--mLives;
	}
}
