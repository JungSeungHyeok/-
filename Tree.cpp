#include "Tree.h"
#include "Utils.h"
#include "InputMgr.h"
#include "Player.h"

class Player;

Tree::Tree(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), countOfBranches(6), branches(countOfBranches), branchPositions(countOfBranches), currentBranch(0)
{
	texBranch.loadFromFile("graphics/branch.png");
	texLog.loadFromFile("graphics/log.png");

	for (auto& branch : branches)
	{
		branch = new Branch(texBranch, { -1.f, -1.f}, "Branch");
		branch->SetTree(this);
	}

	for (int i = 0; i < 100; i++)
	{
		EffectGo* newGo = new EffectGo(texLog);
		newGo->SetActive(false);
		logPool.push_back(newGo);
	}

}

Tree::~Tree()
{

}

void Tree::Init()
{
	SpriteGo::Init();

	currentBranch = 0; // �̾��Ҳ��� �ϸ� �ȵ�

	float x = GetPosition().x;
	float y = 800.f;
	float offset = branches[0]->GetSize().y + 100;

	for (int i = 0; i < branchPositions.size(); ++i)
	{
		branchPositions[i].x = x;
		branchPositions[i].y = y;
		y -= offset;
	}

	for (int i = 0; i < branchPositions.size(); ++i) // �̾��Ҳ��� �ϸ� �ȵ�
	{
		branches[i]->Init();
		branches[i]->SetPosition(branchPositions[i]);
		Sides side = (Sides)Utils::RandomRange(0, 1);
		branches[i]->SetSide(side);
	}

	//for (auto& log : logEffects)
	//{
	//	log->SetActive()
	//}
}

void Tree::Release()
{
	SpriteGo::Release();
	
	for (auto& branch : branches)
	{
		delete branch;
		branch = nullptr;
	}
	branches.clear();
	
	for (auto& effect : logPool)
	{
		delete effect;
		effect = nullptr;
	}
	logPool.clear();
	for (auto& effect : logEffects)
	{
		delete effect;
		effect = nullptr;
	}
	logEffects.clear();
}

void Tree::Update(float dt, int& score, float& timer, float& duration)
{
	SpriteGo::Update(dt, score, timer, duration);

	/*if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		UpdateBranches();
	}*/

	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		sf::Vector2f pos = GetPosition();
		pos.y = GetSize().y;
		ShowEffectLog(Sides::Left, pos);
		UpdateBranches();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		sf::Vector2f pos = GetPosition();
		pos.y = GetSize().y;
		ShowEffectLog(Sides::Right, pos);
		UpdateBranches();
	}


	auto it = logEffects.begin();
	while (it != logEffects.end())
	{
		if ((*it)->GetActive())
		{
			(*it)->Update(dt, score, timer, duration);
			++it;
		}
		else
		{
			logPool.push_back(*it);
			it = logEffects.erase(it); // �̷����� �Լ��� �Ű������� ���ͷ�����
			
		}
	}
	//stl �����̳� ��ȸ�� ����

	for (auto effect : logEffects)
	{
		if (effect->GetActive())
		{
			effect->Update(dt, score, timer, duration);
		}
		else
		{
			//logEffects
			//logPool
		}

	}
}

void Tree::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	for (auto branch : branches)
	{
		branch->Draw(window);
	}
	for (auto effect : logEffects)
	{
		effect->Draw(window);
	}
}

void Tree::UpdateBranches()
{
	float time = 0.f;
	float interval = 0.f;

	//if (player->BranchDie())  //  �ٷ� �״°� ó��
	//{

	//}

	currentBranch = (currentBranch + 1) % branches.size();

	for (int i = 0; i < branches.size(); ++i)
	{
		int index = (currentBranch + i) % branches.size();
		branches[index]->SetPosition(branchPositions[i]);
		if (i == branches.size() - 1)
		{
			Sides side = (Sides)Utils::RandomRange(0, 1);
			branches[index]->SetSide(side);
		}
	}
}


void Tree::ShowEffectLog(Sides side, sf::Vector2f position)
{
	if (logPool.empty()) // ����Ƽ�� ��������� Ʈ��
	{
		std::cout << "Log Pool Empty" << std::endl; // �� �޽����� ��ٸ� Ǯ�� ����� �ø��ų� �ؾ��Ѵ�
		return; // �����߻��Ҽ� ������ ����ؾ��Ѵ�
	}

	EffectGo* log = logPool.front(); // ���� �տ� ���� ���۷��� �������ִ°�
	logPool.pop_front(); // �Ǿտ��ִ°Ÿ� ���°�
	logEffects.push_back(log);
	// 1. �ּҰ����� 2. �����Դ� �Ÿ� ����Ʈ���� ���� 3. Ǫ������ �����Ÿ� �ǵڷ�

	log->SetActive(true);
	log->Init();
	log->SetPosition(position);

	log->Fire(sf::Vector2f(side == Sides::Right ? 1000.f : -1000.f, -1000.f));


}

Sides Tree::GetBranch(void)
{
	return branches[currentBranch]->GetSide();
}

