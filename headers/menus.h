#ifndef MENUS_H
#define MENUS_H

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
	public:
		Menu();
		void showMenu(int choice, sf::RenderWindow&);
		void displayMainMenu();
		void displayPauseMenu(sf::RenderWindow&);
		void handleInput();
	private:
		std::vector<std::string> options = {"Main", "Pause"};
		bool isPaused;
};

#endif
