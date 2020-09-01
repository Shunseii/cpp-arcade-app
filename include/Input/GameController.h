#ifndef INPUT_GAMECONTROLLER_H
#define INPUT_GAMECONTROLLER_H

#include <vector>
#include "Input/InputAction.h"

class GameController {
	private:
		std::vector<ButtonAction> mButtonActions;
		std::vector<MouseButtonAction> mMouseButtonActions;
		MouseMovedAction mMouseMovedAction;

	public:
		GameController();

		InputAction GetActionForKey(InputKey key);
		void AddInputAction(const ButtonAction&);
		void ClearAll();

		static bool IsPressed(InputState state);
		static bool IsReleased(InputState state);
		
		// Actions keys
		static InputKey ActionKey();
		static InputKey CancelKey();
		static InputKey LeftKey();
		static InputKey RightKey();
		static InputKey UpKey();
		static InputKey DownKey();

		inline const MouseMovedAction& GetMouseMovedAction() {return mMouseMovedAction;}
		inline void SetMouseMovedAction(const MouseMovedAction& action) {mMouseMovedAction = action;}

		MouseInputAction GetMouseButtonActionForMouseButton(MouseButton button);
		void AddMouseButtonAction(const MouseButtonAction& action);

		static MouseButton LeftMouseButton();
		static MouseButton RightMouseButton();
};

#endif
