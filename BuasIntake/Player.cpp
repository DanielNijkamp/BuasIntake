#include "Player.h"

#include <iostream>

void Player::Update(float deltaTime)
{
    velocity = (velocity < 0.01 && velocity > -0.01) ? velocity = 0 : velocity *= 0.90f;
    
    Move(deltaTime);
    Rotate(deltaTime);
    Deaccelerate();
}


void Player::AddDrunkenness(float strength)
{
    drunkenness += strength;
    
    if (drunkenness > maxDrunkenness) {
        drunkenness = maxDrunkenness;
    }
}

void Player::Accelerate(const float step) const
{
    acceleration = std::min(acceleration + step, maxAcceleration);
}

void Player::Deaccelerate() const
{
    acceleration = std::max(acceleration - accelerationStep / 2, minAcceleration);
}

void Player::Steer(float direction)
{
    velocity += direction - (swerveResistance * sin(drunkenness));
}

void Player::Move(float deltaTime)
{
    float drunkenEffect = sin(drunkenness) * swerveStrength; 
    drunkenness = std::max(drunkenness - deltaTime * soberStep, 0.0f);
    
    if (drunkenness == minDrunkenness) {
        onSober.Fire();
    }
    
    float positionX = position.x + velocity * deltaTime + drunkenEffect;
    UpdatePositions(sf::Vector2f(positionX, position.y));
    
    const sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    UpdateCollision();  
}
void Player::Rotate(float deltaTime)
{
    float drunkenRotation = sin(drunkenness) * 10.0f;
    
    float absVelocity = abs(velocity * deltaTime);
    float rotationMagnitude = (absVelocity > 45 ? 45.0f : absVelocity) * 2;
    
    float desiredRotation = velocity > 0 ? rotationMagnitude : -rotationMagnitude;
    desiredRotation += drunkenRotation;
    
    float currentRotation = sprite.getRotation();
    
    currentRotation = std::fmod(currentRotation, 360);
    if (currentRotation > 180) {
        currentRotation -= 360;
    }
    
    float timeFactor = 1;
    
    if(std::abs(desiredRotation - currentRotation) > 180) {
        currentRotation += currentRotation < desiredRotation ? 360.f : -360.f;
    }
    
    float newRotation = ((1 - timeFactor) * currentRotation + timeFactor * desiredRotation);
    
    sprite.setRotation(newRotation);
}

void Player::Init()
{
    this->input.SubscribeToContinuousKey(sf::Keyboard::Key::W,
    [this] { Accelerate(accelerationStep); });
		
    this->input.SubscribeToContinuousKey(sf::Keyboard::Key::S,
    [this] { Accelerate(-accelerationStep); });
		
    this->input.SubscribeToContinuousKey(sf::Keyboard::Key::A,
    [this] { Steer( -steerStrength); });
		
    this->input.SubscribeToContinuousKey(sf::Keyboard::Key::D,
    [this] { Steer( steerStrength); });
}