#include "EffectGo.h"

EffectGo::EffectGo(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, 
	const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), gravity(0.f, 2000.f), duration(3.f), timer(0.f)
{
	SetOrigin(Origins::MC);
}

EffectGo::~EffectGo()
{
}

void EffectGo::Fire(sf::Vector2f v)
{
	velocity = v;
}

void EffectGo::Init()
{
	SpriteGo::Init();

	timer = 0.f;
}

void EffectGo::Release()
{
	SpriteGo::Release();
}

void EffectGo::Update(float dt, int& score, float& timer, float& duration)
{
	SpriteGo::Update(dt, score, timer, duration);

	this->timer += dt; // this ¼öÁ¤
	if (this->timer > this->duration)
	{
		SetActive(false);
		return;
	}

	velocity += gravity * dt;
	SetPosition(position + velocity * dt);
}

void EffectGo::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
