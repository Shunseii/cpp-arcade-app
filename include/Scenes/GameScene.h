#ifndef SCENES_GAMESCENE_H
#define SCENES_GAMESCENE_H

#include <memory>
#include "Scenes/Scene.h"
#include "Games/Game.h"

class GameScene: public Scene {
	private:
		std::unique_ptr<Game> mGame;

	public:
		GameScene(std::unique_ptr<Game> optrGame);
		virtual ~GameScene() {}

		virtual void Init() override;
		virtual void Update(uint32_t dt) override;
		virtual void Draw(Screen&) override;

		virtual const std::string& GetSceneName() const override;
};

#endif
