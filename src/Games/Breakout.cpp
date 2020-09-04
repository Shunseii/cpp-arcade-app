#include "Games/Breakout.h"

#include <iostream>

void Breakout::Init(GameController&) {
	std::cout << "Breakout Game Init" << std::endl;
}

void Breakout::Update(uint32_t dt) {
	std::cout << "Breakout Game Update" << std::endl;
}

void Breakout::Draw(Screen& screen) { 	
	std::cout << "Breakout Game Draw" << std::endl;
}

std::string Breakout::GetName() const {
	return "Breakout";
}
