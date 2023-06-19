#pragma once
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "SpriteGo.h"
#include "Branch.h"
#include "EffectGo.h"

class Tree : public SpriteGo
{
protected:
	const int countOfBranches;
	std::vector<Branch*> branches;
	std::vector<sf::Vector2f> branchPositions;
	int currentBranch;
	sf::Texture texBranch;

	std::list<EffectGo*> logPool; // 비활성화 들고있으면 풀
	std::list<EffectGo*> logEffects;

	sf::Texture texLog;

public:
	Tree(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	~Tree() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt, int &score, float &timer, float &duration) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void UpdateBranches();
	void ShowEffectLog(Sides side, sf::Vector2f position); // 사이드 줘서 왼쪽인지, 오른쪽;인지

	Sides GetBranch(void);

};

