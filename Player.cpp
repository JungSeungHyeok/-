#include "Player.h"
#include "Tree.h"
#include "InputMgr.h"
#include "EffectGo.h"
#include "Defines.h"

Player::Player(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), offsetX(100.f), isChopping(false), texPlayer(tex)
	 // score(nullptr), timer(nullptr), duration(0.0f)
{
	texAxe.loadFromFile("graphics/axe.png");
	axe = new SpriteGo(texAxe);

	SetOrigin(Origins::BC);

	for (auto& position : playerPositions)
	{
		position = p;
	}

	texRip.loadFromFile("graphics/rip.png");

	soundBufferChop.loadFromFile("sound/chop.wav");
	soundBufferDeath.loadFromFile("sound/death.wav");
	soundBufferOutoftime.loadFromFile("sound/out_of_time.wav");

	soundChop.setBuffer(soundBufferChop);
	soundDeath.setBuffer(soundBufferDeath);
	soundOutoftime.setBuffer(soundBufferOutoftime);

}

Player::~Player()
{
}

bool Player::BranchDie()
{
	return this->side != tree->GetBranch();


	// return true;
}

//void Player::BranchDie()
//{
//	// 여기 구현인데 아직 못함
//	Die();
//
//}
//
//int Player::GetScore() const
//{
//	return *score; // 아직 작동안됨
//}

void Player::SetTree(Tree* tree)
{
	this->tree = tree;
}

void Player::SetSide(Sides side)
{
	this->side = side;

	SetPosition(playerPositions[(int)this->side]);
	SetFlipX(this->side == Sides::Right);

	axe->SetPosition(GetPosition());
	axe->SetFlipX(this->side == Sides::Right);
}

Sides Player::GetSide() const
{
	return side;
}

void Player::Chop(Sides side)
{
	SetSide(side);
	isChopping = true;

	// 통나무 날리는 연출
}

void Player::Die(float timer)
{
	isAlive = false;
	isChopping = false;

	if (timer > 0.f)
	{
		soundDeath.play();
	}
	else
	{
		soundOutoftime.play();
	}

	SetTexture(texRip);
	SetOrigin(Origins::BC);
	SetFlipX(true);
	
}

void Player::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
}

void Player::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
}

void Player::Init()
{
	isAlive = true;
	SetTexture(texPlayer);
	SetOrigin(Origins::BC);

	isChopping = false;

	SpriteGo::Init();

	sf::Vector2f playerSize = GetSize();

	float treeHalfWidth = tree->GetSize().x * 0.5f;
	float playerHalfWidth = playerSize.x * 0.5f;
	float delta = treeHalfWidth + playerHalfWidth + offsetX;

	playerPositions[(int)Sides::Left].x = tree->GetPosition().x - delta;
	playerPositions[(int)Sides::Right].x = tree->GetPosition().x + delta;

	sf::Vector2f axeSize = axe->GetSize();
	axe->SetOrigin(axeSize.x + playerHalfWidth, playerSize.y * 0.45f);

	axe->Init();
	axe->SetPosition(GetPosition());

	SetSide(Sides::Right);
}

void Player::Release()
{
	delete axe;
	axe = nullptr;

	SpriteGo::Release();
}

void Player::Update(float dt, int& score, float& timer, float& duration)
{
	SpriteGo::Update(dt, score, timer, duration);

	

	if (!isAlive)
	{
		return;
	}
	SpriteGo::Update(dt, score, timer, duration);

	if (!isChopping)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			Chop(Sides::Left);
			soundChop.play();
			score += 10;
			timer += 0.1f;
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			Chop(Sides::Right);
			soundChop.play();
			score += 10;
			timer += 0.1f;

		}
	}

	else
	{
		if (GetSide() == Sides::Left &&
			InputMgr::GetKeyUp(sf::Keyboard::Left))
		{
			isChopping = false;
		
		}
		if (GetSide() == Sides::Right &&
			InputMgr::GetKeyUp(sf::Keyboard::Right))
		{
			isChopping = false;
			
		}
	}

	axe->Update(dt, score, timer, duration);
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

	if (isChopping)
	{
		axe->Draw(window);
	}
}

void Player::SoundDeath()
{
	soundDeath.play();
}

void Player::SoundChop()
{
	soundChop.play();
}

void Player::SoundOutoftime()
{
	soundOutoftime.play();
}



//if (InputMgr::GetKeyDown(sf::Keyboard::Num3)) // 죽기
	//{
	//	Die();
	//}

	//if (InputMgr::GetKeyDown(sf::Keyboard::Num4)) // 살려보기
	//{
	//	Init();
	//}