#pragma once
#include "Objects/Spawners/Car/Car.h"
#include "Behaviour/FixedUpdatable.h"
#include "Behaviour/Transformable.h"
#include "Systems/Input.h"

class Player final : public Car, public FixedUpdatable
{
public:
	explicit Player(
		const sf::Sprite& sprite,
		Input& input,
		const sf::Vector2f position,
		float& acceleration,
		const float minAcceleration,
		const float maxAcceleration,
		const float accelerationStep,
		const float steerStrength,
		const float initialDrunkenness,
		const float minDrunkenness,
		const float maxDrunkenness,
		const float swerveStrength,
		const float soberStep,
		const float swerveResistance)
		:
		Car(position, sprite),
		drunkenness(initialDrunkenness),
		minDrunkenness(minDrunkenness),
		maxDrunkenness(maxDrunkenness),
		swerveStrength(swerveStrength),
		soberStep(soberStep),
		swerveResistance(swerveResistance),
		acceleration(acceleration),
		minAcceleration(minAcceleration),
		maxAcceleration(maxAcceleration),
		accelerationStep(accelerationStep),
		steerStrength(steerStrength),
		input(input)
	{
		Init();
		Car::UpdatePositions(position);
	}

	void Update(float deltaTime) override;
	
	void AddDrunkenness(float strength);
	
	Event<> onSober; //fires once drunkenness hits minDrunkenness, acts as lose condition
	sf::Vector2f prevPosition;

	//we can also define a get method but idk about if readonly is possible
	float drunkenness;
private:
	void Init();
	
	void Steer(float direction);
	void Move(float deltaTime);
	void Rotate(float deltaTime);
	
	void Accelerate(float step) const;
	void Deaccelerate() const;
	
	const float minDrunkenness; //minimum acts as the lose condition
	const float maxDrunkenness; //any strength added by bottles will be clamped by this value
	
	const float swerveStrength; //how much the player will swerve left and right
	const float soberStep; //by how much reduce drunkenness each step
	const float swerveResistance; //how much resistance the player's movement has agianst the swerving
	
	//floats used for movement
	float velocity = 0.0f;
	float& acceleration; //this float is modifier externally and the player only reads it
	float minAcceleration;
	float maxAcceleration;
	float accelerationStep;
	const float steerStrength;

	//shared_ptr or raw pointer or reference? keep as ref for now.
	Input& input;
};

