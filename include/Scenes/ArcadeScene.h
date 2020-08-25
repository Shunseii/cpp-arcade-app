#ifndef SCENES_ARCADE_SCENE_H
#define SCENES_ARCADE_SCENE_H

#include "Scenes/Scene.h"
#include <memory>

enum eGame {
	TETRIS = 0,
	BREAK_OUT,
	ASTEROIDS,
	PACMAN,
	NUM_GAMES
};

class Screen;

class ArcadeScene: public Scene {
	private:
		std::unique_ptr<Scene> GetScene(eGame game);

	public:
		ArcadeScene();
		virtual void Init() override;
		virtual void Update(uint32_t dt) override;
		virtual void Draw(Screen&) override;
		virtual const std::string& GetSceneName() const override;
};

#endif
