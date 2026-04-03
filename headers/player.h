#include <SFML/Graphics.hpp>
#include "animation.h"
#include "platform.h"
#include <SFML/Window.hpp>
class Player{
	public:
		Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
		~Player();
		void Update(float deltaTime, std::vector<Platform>& platforms);
		void Draw(sf::RenderWindow& window);
		sf::Vector2f GetPosition(){return body.getPosition();};
		float getX(){return body.getPosition().x;};
		float getY(){return body.getPosition().y;};
		void resolveCollisions(std::vector<Platform>& platforms);
		sf::FloatRect getBounds();
		void applyGravity(float deltaTime);
		void jump(float deltaTime);
	private:
		sf::RectangleShape body;
		Animation animation;
		unsigned int row;
		float speed;
		bool faceRight;
		const float gravity = 2.9;
		bool isOnGround;
		sf::Vector2f velocity;
		const float terminalVelocity = 4; //adjust as we go
};
