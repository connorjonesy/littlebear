#include "../headers/player.h"
#include "../headers/platform.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture,imageCount,switchTime){
	this->speed = speed;
	row = 0;
 	faceRight = true;
	isOnGround = true;
	velocity = {0.0f,0.0f};
	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition({375,275}); 
	body.setTexture(texture);
	}

Player::~Player(){}

sf::FloatRect Player::getBounds(){
	//This func is needed to overload the getGlobalBounds in order to account for whitespace around lb
	sf::FloatRect globalBounds = body.getGlobalBounds();

	float trimXRatio = 63.f  / 250.f; // ~0.252
	float trimYRatio = 100.f / 250.f; // ~0.4
	float trimWRatio = 126.f / 250.f; // ~0.504
	float trimHRatio = 100.f / 250.f; // ~0.4

	float trimX = globalBounds.size.x * trimXRatio;
	float trimY = globalBounds.size.y * trimYRatio;
	float trimW = globalBounds.size.x * trimWRatio;
	float trimH = globalBounds.size.y * trimHRatio;

	return sf::FloatRect(
		sf::Vector2f(globalBounds.position.x + trimX, globalBounds.position.y + trimY),
		sf::Vector2f(globalBounds.size.x - trimW, globalBounds.size.y - trimH)
	);
}

void Player::resolveCollisions(std::vector<Platform>& platforms){
	isOnGround = false;
	for (auto& platform : platforms) {
		if (!getBounds().findIntersection(platform.getBounds()))
			continue; // no overlap, skip

		// Figure out overlap on each axis
		sf::FloatRect player = getBounds();
		sf::FloatRect plat   = platform.getBounds();
		
		float overlapLeft   = (player.position.x + player.size.x) - plat.position.x;
		float overlapRight  = (plat.position.x + plat.size.x) - player.position.x;
		float overlapTop    = (player.position.y + player.size.y) - plat.position.y;
		float overlapBottom = (plat.position.y + plat.size.y) - player.position.y;

		// Find the smallest overlap — that's the axis to resolve on
		bool fromLeft = std::abs(overlapLeft) < std::abs(overlapRight);
		bool fromTop = std::abs(overlapTop) < std::abs(overlapBottom);

		float minXOverlap = fromLeft ? overlapLeft : overlapRight;
		float minYOverlap = fromTop ? overlapTop : overlapBottom;

		if (std::abs(minXOverlap) < std::abs(minYOverlap)) {
			// Horizontal collision
			body.move({fromLeft ? -overlapLeft : overlapRight, 0.f});
		} else {
			// Vertical collision
			body.move({0.f, fromTop ? -overlapTop : overlapBottom});
			if (fromTop) {
				velocity.y = 0.f;
				isOnGround = true;
			}
		}
	}
}

void Player::applyGravity(float deltaTime){
	if(isOnGround == true){
		return;
	}
	if(velocity.y < terminalVelocity){
		//lil b is in the air, increase velocity
		velocity.y += gravity * deltaTime;
	}
}

void Player::jump(float deltaTime){
	velocity.y -= 2*gravity * deltaTime;
}

void Player::Update(float deltaTime, std::vector<Platform>& platforms){
	velocity.x = 0.0f;
	//velocity.y = 0.0f; // uncomment for testing
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		velocity.x -= speed * deltaTime;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
		velocity.x += speed * deltaTime;
	}
	/*
	 // * Uncomment for testing
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		velocity.y -= speed * deltaTime;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
		velocity.y += speed * deltaTime;
	}
	*/
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
		jump(deltaTime);
	}
	if(velocity.x == 0.0f){
		//idle animation		
		animation.Update(row,deltaTime,faceRight, true);
	}else{
		if(velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;

		animation.Update(row, deltaTime, faceRight,false);
	}
	applyGravity(deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(velocity);
	resolveCollisions(platforms);
}

void Player::Draw(sf::RenderWindow& window){
	window.draw(body);
}
