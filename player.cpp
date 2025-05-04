#include "headers/player.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture,imageCount,switchTime){
	this->speed = speed;
	row = 0;
 	faceRight = true;
	body.setSize(sf::Vector2f(256.0f, 250.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(375,275); 
	body.setTexture(texture);
	}

Player::~Player(){}

bool collision(float coordsx, float coordsy){
	return false;
}

void Player::Update(float deltaTime, float playercoordsx, float playercoordsy){
	sf::Vector2f movement(0.0f, 0.0f);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= speed * deltaTime;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !collision(playercoordsx,playercoordsy)){
		movement.x += speed * deltaTime;
		std::cout << "d pressed ";
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= speed * deltaTime * 2;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += speed * deltaTime * 2;
	
	if(movement.x == 0.0f){
		//idle animation		
		animation.Update(row,deltaTime,faceRight, true);
	}else{

		if(movement.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;

		animation.Update(row, deltaTime, faceRight,false);
	}
	
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window){
	window.draw(body);
}
