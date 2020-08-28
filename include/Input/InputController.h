#ifndef INPUT_INPUTCONTROLLER_H
#define INPUT_INPUTCONTROLLER_H

#include "Input/InputAction.h"

struct GameController;

class InputController {
	private:
		InputAction mQuit;
		GameController* mnoptrCurrentController;

	public:
		InputController();
		void Init(InputAction quitAction);
		void Update(uint32_t dt);
		void SetGameController(GameController* controller);
};

#endif
