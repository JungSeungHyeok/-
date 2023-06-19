#include "Utils.h"

using namespace std;

random_device Utils::rd;
mt19937 Utils::gen(Utils::rd());

int Utils::RandomRange(int min, int maxExclude)
{
	uniform_int_distribution<> dist(min, maxExclude);
	return dist(gen);
	// return gen() % (maxExclude - min) + min; // 맥스에서 민 빼면 값의 범위가나옴
	// 원하는 정수값의 식
}

float Utils::RandomRange(float min, float max)
{
	uniform_real_distribution<> dist(min, max);
	return (float)dist(gen);
}

void Utils::SetOrigin(sf::Sprite& sprite, Origins origin)
{
	SetOrigin(sprite, origin, sprite.getLocalBounds());
}

void Utils::SetOrigin(sf::Text& text, Origins origin)
{
	SetOrigin(text, origin, text.getLocalBounds());
}

void Utils::SetOrigin(sf::Shape& Shape, Origins origin)
{
	SetOrigin(Shape, origin, Shape.getLocalBounds());
}

void Utils::SetOrigin(sf::Transformable& obj, Origins origin, const sf::FloatRect& rect)
{
	sf::Vector2f originPos(rect.width, rect.height);
	originPos.x *= ((int)origin % 3) * 0.5f; // 0 or 0.5 or 1
	originPos.y *= ((int)origin / 3) * 0.5f;
	obj.setOrigin(originPos);
}
