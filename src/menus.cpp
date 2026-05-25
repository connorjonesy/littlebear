#include <SFML/Graphics.hpp>
#include "../headers/menus.h"
#include <iostream>

Menu::Menu(){};

void Menu::showMenu(int choice, sf::RenderWindow& window){
	std::string selection;
	switch(choice){
		case 0:
			displayMainMenu();
			break;
		case 1:
			displayPauseMenu(window);
			break;
		default:
			std::cout << "Not a valid selection for a menu" << std::endl;
			break;
	}
}

void Menu::displayPauseMenu(sf::RenderWindow& window){
	sf::RectangleShape menu_UI;
	menu_UI.setSize({400.0f, 100.0f});
	menu_UI.setFillColor(sf::Color::Black);
	menu_UI.setPosition({400.0f,200.0f});
	sf::Font font;
	if (!font.openFromFile("../assets/NorthernBack.ttf"))
		std::cout << "Couldnt open the font lad" << std::endl;
	sf::Text exit_text(font, "Exit to Destop", 44);
	exit_text.setFillColor(sf::Color::White);
	exit_text.setPosition({400.0f, 200.0f});

	window.draw(menu_UI);
	window.draw(exit_text);

	//if user clicks button
	    //window.close();

}

void Menu::displayMainMenu(){
}
