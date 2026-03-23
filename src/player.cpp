#include "../headers/player.h"
#include "../headers/platform.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture,imageCount,switchTime){
	this->speed = speed;
	row = 0;
 	faceRight = true;
	gravity = 9.81;
	isOnGround = false;
	velocity = {0.0f,0.0f};
	body.setSize(sf::Vector2f(250.0f, 250.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition({375,275}); 
	body.setTexture(texture);
	}

Player::~Player(){}

void Player::resolveCollisions(std::vector<Platform>& platforms){
	isOnGround = false;
	for (auto& platform : platforms) {
		if (!getBounds().findIntersection(platform.getBounds()))
			continue; // no overlap, skip

		// Figure out overlap on each axis
		sf::FloatRect player = getBounds();
		sf::FloatRect plat   = platform.getBounds();
		//TODO:: Change the bounds for the player cuz theres whitespace around the bear
		float overlapLeft   = (player.position.x + player.size.x - 100) - plat.position.x;
		float overlapRight  = (plat.position.x + plat.size.x)     - player.position.x;
		float overlapTop    = (player.position.y + player.size.y)  - plat.position.y;
		float overlapBottom = (plat.position.y + plat.size.y)      - player.position.y;

		// Find the smallest overlap — that's the axis to resolve on
		bool fromLeft  = std::abs(overlapLeft)  < std::abs(overlapRight);
		bool fromTop   = std::abs(overlapTop)   < std::abs(overlapBottom);

		float minXOverlap = fromLeft  ? overlapLeft  : overlapRight;
		float minYOverlap = fromTop   ? overlapTop   : overlapBottom;

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

void Player::Update(float deltaTime, std::vector<Platform>& platforms){
	velocity = {0.0f,0.0f};
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		velocity.x -= speed * deltaTime;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
		velocity.x += speed * deltaTime;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		velocity.y -= speed * deltaTime;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
		velocity.y += speed * deltaTime;
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
	//add gravity
	velocity.y += gravity * deltaTime;
	body.setTextureRect(animation.uvRect);
	body.move(velocity);
	resolveCollisions(platforms);
}

void Player::Draw(sf::RenderWindow& window){
	window.draw(body);
}
