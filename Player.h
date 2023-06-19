#pragma once
#include "SpriteGo.h"
#include "Defines.h"
#include <SFML/Audio.hpp>

class Tree;

class Player : public SpriteGo
{
protected:
	Tree* tree;
	Sides side;

	SpriteGo* axe;

	float offsetX;
	sf::Vector2f playerPositions[2];

	bool isChopping;
	bool isAlive;

	sf::Texture texAxe;
	sf::Texture texRip; // 비석 텍스쳐
	sf::Texture& texPlayer;

	sf::SoundBuffer soundBufferChop;
	sf::SoundBuffer soundBufferDeath;
	sf::SoundBuffer soundBufferOutoftime;

	sf::Sound soundChop;
	sf::Sound soundDeath;
	sf::Sound soundOutoftime;

public:
	Player(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	~Player();

	bool BranchDie();
	//int GetScore() const;

	void SetTree(Tree* tree);

	void SetSide(Sides side);
	Sides GetSide() const;

	void Chop(Sides side);
	void Die(float timer);

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void Init();
	virtual void Release();

	virtual void Update(float dt, int& score, float& timer, float& duration);
	virtual void Draw(sf::RenderWindow& window);

	void SoundDeath();
	void SoundChop();
	void SoundOutoftime();
};

