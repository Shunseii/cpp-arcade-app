#include <iostream>
#include "App/App.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 1;

int main(int argc, char* argv[]) {
	if (App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION)) {
		App::Singleton().Run();
	}

	return 0;
}
