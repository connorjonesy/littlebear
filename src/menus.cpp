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
	//TODO fix hardcoded centering of UI elements
	sf::RectangleShape menu_UI;
	menu_UI.setSize({264.0f, 100.0f});
	menu_UI.setOrigin({float(menu_UI.getSize().x / 2.f),0.0f});
	menu_UI.setPosition({window.getSize().x / 2.f,300.0f});
	menu_UI.setFillColor(sf::Color::Black);

	sf::Font font;
	if (!font.openFromFile("../assets/NorthernBack.ttf"))
		std::cout << "Couldnt open the font lad" << std::endl;
	sf::Text exit_text(font, "Exit to Desktop", 44);
	exit_text.setOrigin({float(menu_UI.getSize().x / 2.f),0.0f});
	exit_text.setPosition({float(window.getSize().x) / 2.f, 320.0f});
	exit_text.setFillColor(sf::Color::White);


	sf::Vector2i localMousePos = sf::Mouse::getPosition(window); //relative to the window
	sf::Vector2f f_localMousePos = {float(localMousePos.x), float(localMousePos.y)};
	std::cout << "Mouse x,y: (" << localMousePos.x << "," << localMousePos.y << ")" << std::endl;
	
	bool mouseClicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	bool mouseOverExitButton = false;

	if(menu_UI.getGlobalBounds().contains(f_localMousePos)){
		mouseOverExitButton = true;
		//Highlight the Exit Button
		menu_UI.setFillColor(sf::Color::Magenta);
		exit_text.setFillColor(sf::Color::Black);
	}else{
		mouseOverExitButton = false;
		//Remove hover button colour
		menu_UI.setFillColor(sf::Color::Black);
		exit_text.setFillColor(sf::Color::White);
	}
	
	window.draw(menu_UI);
	window.draw(exit_text);

	if(mouseOverExitButton && mouseClicked){
		std::cout << "User is exiting to desktop" << std::endl;
		window.close();
	}
}

void Menu::displayMainMenu(){
}
