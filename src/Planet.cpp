#include "Planet.h"
#include "Game.h"

Planet::Planet():
	m_currentTile(NULL)
{
	TheTextureManager::Instance()->load("../Assets/textures/ball.png",
		"planet", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("planet");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(Util::RandomRange(-1.0f, 1.0f), Util::RandomRange(-1.0f, 1.0f)));
	setIsColliding(false);
	setType(GameObjectType::PLANET);
}

Planet::~Planet()
{
}

void Planet::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("planet", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);
}

void Planet::update()
{
	m_checkBounds();
	m_move();
}

void Planet::clean()
{
	delete m_currentTile;
	m_currentTile = NULL;
}

Tile * Planet::getTile()
{
	return m_currentTile;
}

void Planet::setTile(Tile * newTile)
{
	m_currentTile = newTile;
}

void Planet::m_move()
{

	glm::vec2 newPosition = getPosition() + getVelocity() * 15.0f;
	if (newPosition.y > 768.0f)
	{
		newPosition = glm::vec2(getPosition().x, 768);
	}
	setPosition(newPosition);
	
}

void Planet::m_checkBounds()
{
	if ((getPosition().y + getHeight() / 2) > 768.0f && getVelocity().y >= 0.0f)
	{
		setVelocity(glm::vec2(getVelocity().x, -getVelocity().y * 0.45));
	}
	if ((getPosition().y < (getHeight() * 0.5f)) && getVelocity().y < 0.0f)
	{
		setVelocity(glm::vec2(getVelocity().x, -getVelocity().y * 0.45));
	}
	if (getPosition().x + getWidth() * 0.5f > 1024.0f && getVelocity().x >= 0.0f)
	{
		setVelocity(glm::vec2(-getVelocity().x * 0.45, getVelocity().y));
	}
	if (getPosition().x < (getHeight() * 0.5f) && getVelocity().x < 0.0f)
	{
		setVelocity(glm::vec2(-getVelocity().x * 0.45, getVelocity().y));
	}
}

void Planet::m_reset()
{

}
