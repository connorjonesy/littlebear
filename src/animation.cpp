#include "../headers/animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime){
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.size.x = texture->getSize().x / float(imageCount.x);
	uvRect.size.y = texture->getSize().y / float(imageCount.y);
}


Animation::~Animation(){}

void Animation::Update(int row, float deltaTime, bool faceRight, bool idle){
	currentImage.y = row;
	totalTime += deltaTime;
	if(!idle){
	if(totalTime >= switchTime){
		totalTime -= switchTime;
		currentImage.x++;

		if(currentImage.x >= imageCount.x){
			currentImage.x = 0;
		}
	}
	}else{
		currentImage.x = 3;
	}
	
	uvRect.position.y = currentImage.y * uvRect.size.y;

	if(faceRight){
		uvRect.position.x = currentImage.x *uvRect.size.x;
		uvRect.size.x = abs(uvRect.size.x);
	}else{
		uvRect.position.x = (currentImage.x + 1) * abs(uvRect.size.x);
		uvRect.size.x = -abs(uvRect.size.x);
	}
}
