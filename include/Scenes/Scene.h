#ifndef SCENES_SCENE_H
#define SCENES_SCENE_H

#include <string>
#include <stdint.h>

#include "Input/GameController.h"

class Screen;

// Scene Interface
class Scene {
	public:
		virtual ~Scene() {}
		virtual void Init() = 0;
		virtual void Update(uint32_t dt) = 0;
		virtual void Draw(Screen&) = 0;
		virtual const std::string& GetSceneName() const = 0; 
		
		inline GameController* GetGameController() {return &mGameController;}

	protected:
		GameController mGameController;
};

#endif
