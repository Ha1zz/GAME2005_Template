#include "CollisionManager.h"
#include "Util.h"


int CollisionManager::squaredDistance(glm::vec2 P1, glm::vec2 P2)
{
	int diffOfXs = P2.x - P1.x;
	int diffOfYs = P2.y - P1.y;
	int result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}

bool CollisionManager::squaredRadiusCheck(GameObject * object1, GameObject * object2)
{
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	int halfHeights = (object1->getHeight() + object2->getHeight()) * 0.5;

	//if (glm::distance(P1, P2) < halfHeights) {

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType()) {
			case PLANET:
				std::cout << "Collision with Planet!" << std::endl;
				TheSoundManager::Instance()->playSound("yay", 0);
				break;
			case MINE:
				std::cout << "Collision with Mine!" << std::endl;
				TheSoundManager::Instance()->playSound("thunder", 0);
				break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
		//else
		//{
		//	object2->setIsColliding(false);
		//}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
	}
	
}

bool CollisionManager::lineLineCheck(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 line2Start, glm::vec2 line2End)
{
	float x1 = line1Start.x;
	float x2 = line1End.x;
	float x3 = line2Start.x;
	float x4 = line2End.x;
	float y1 = line1Start.y;
	float y2 = line1End.y;
	float y3 = line2Start.y;
	float y4 = line2End.y;

	// calculate the distance to intersection point
	float uA = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	float uB = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) 
	{
		return true;
	}
	
	return false;
}

bool CollisionManager::lineRectCheck(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 recStart, float recWidth, float recHeight)
{
	float x1 = line1Start.x;
	float x2 = line1End.x;
	float y1 = line1Start.y;
	float y2 = line1End.y;
	float rx = recStart.x;
	float ry = recStart.y;
	float rw = recWidth;
	float rh = recHeight;

	//TODO FIX THIS

	// check if the line has hit any of the rectangle's sides
	// uses the Line/Line function below
	bool left = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx, ry + rh));
	bool right = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx + rw, ry), glm::vec2(rx + rw, ry + rh));
	bool top = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx + rw, ry));
	bool bottom = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry + rh), glm::vec2(rx + rw, ry + rh));

	// if ANY of the above are true, the line
	// has hit the rectangle
	if (left || right || top || bottom) {
		return true;
	}

	return false;
}

bool CollisionManager::AABBCheck(GameObject * object1, GameObject * object2)
{
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	if (P1.x < P2.x + object2->getWidth() &&
		P1.x + object1->getWidth() > P2.x &&
		P1.y < P2.y + object2->getHeight() &&
		object1->getHeight() + P1.y > P2.y)
	{
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType()) {
			case PLANET:
				std::cout << "Collision with Planet!" << std::endl;
				TheSoundManager::Instance()->playSound("yay", 0);
				break;
			case MINE:
				std::cout << "Collision with Mine!" << std::endl;
				TheSoundManager::Instance()->playSound("thunder", 0);
				break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
	}
	else
	{
		object2->setIsColliding(false);
	}
}

int CollisionManager::isCollision(glm::vec2 circleCenter, int circleRadius, glm::vec2 boxStart, int boxWidth, int boxHeight)
{
	float dx = std::max(boxStart.x - circleCenter.x, 0.0f);
	dx = std::max(dx, circleCenter.x - (boxStart.x + boxWidth));
	float dy = std::max(boxStart.y - circleCenter.y, 0.0f);
	dy = std::max(dy, circleCenter.y - (boxStart.y + boxHeight));

	return (dx * dx) + (dy * dy);
}

bool CollisionManager::circleAABBCheck(GameObject * object1, GameObject * object2)
{
	glm::vec2 circleCenter = object1->getPosition();
	int circleRadius = std::max(object1->getWidth() * 0.5f, object1->getHeight() * 0.5f);
	int boxWidth = object2->getWidth();
	int boxHeight = object2->getHeight();
	int halfBoxWidth = object2->getWidth() * 0.5f;
	int halfBoxHeight = object2->getHeight() * 0.5f;

	glm::vec2 boxStart = object2->getPosition() - glm::vec2(boxWidth * 0.5f, boxHeight * 0.5f);

	if (isCollision(circleCenter, circleRadius, boxStart, boxWidth, boxHeight) <= (circleRadius * circleRadius))
	{
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType()) {
			case PLANET:
				std::cout << "Collision with Planet!" << std::endl;
				TheSoundManager::Instance()->playSound("yay", 0);
				break;
			case MINE:
				std::cout << "Collision with Mine!" << std::endl;
				TheSoundManager::Instance()->playSound("thunder", 0);
				break;
			case SHIP:
				std::cout << "Collision with Ship" << std::endl;
				//TheSoundManager::Instance()->playSound("thunder", 0);
				float dx = object1->getPosition().x - (object2->getPosition().x + halfBoxWidth);
				float dy = object1->getPosition().y - (object2->getPosition().y + halfBoxHeight);

				glm::vec2 ref(1.0f,0.0f);
				glm::vec2 vec(object1->getPosition().x - object2->getPosition().x, object1->getPosition().y - object2->getPosition().y);

				float dot = glm::dot(vec, ref);
	
				float angle = acos((dot / Util::magnitude(vec))) * Util::Rad2Deg;

				float velocityX = vec.x * cos(angle);
				float velocityY = vec.y * sin(angle);
				
				if (dx > 0 && dy > 0)
				{
					//if (angle >= 0.0f && angle <= 30.0f)
					//{
					//	object1->setVelocity(glm::vec2(object1->getVelocity().x, object1->getVelocity().y));
					//}
					//if (angle > 30.0f && angle <= 60.0f)
					//{
					//	object1->setVelocity(glm::vec2(object1->getVelocity().x, object1->getVelocity().y));
					//}
					//if (angle > 60.0f && angle >= 90.0f)
					//{
					//	object1->setVelocity(glm::vec2(object1->getVelocity().x, object1->getVelocity().y));
					//}
					cout << "Bullet from the top left " << endl;
					object1->setVelocity(glm::vec2(object1->getVelocity().x + velocityX, object1->getVelocity().y + velocityY));
				}
				if (dx < 0 && dy > 0)
				{
					//if (angle >= 90.0 && angle <= 120.0f)
					//{
					//	object1->setVelocity(glm::vec2(object1->getVelocity().x, -object1->getVelocity().y));
					//}
					//if (angle > 120.0f && angle <= 150.0f)
					//{
					//	object1->setVelocity(glm::vec2(-object1->getVelocity().x, object1->getVelocity().y));
					//}
					//if (angle > 150.0f && angle >= 180.0f)
					//{
					//	object1->setVelocity(glm::vec2(-object1->getVelocity().x, object1->getVelocity().y));
					//}
					cout << "Bullet from the top right" << endl;
					object1->setVelocity(glm::vec2(object1->getVelocity().x + velocityX, -(object1->getVelocity().y + velocityY)));
				}
				if (dx > 0 && dy < 0)
				{
					//if (angle >= 0.0f && angle <= 30.0f)
					//{
					//	object1->setVelocity(glm::vec2(object1->getVelocity().x, object1->getVelocity().y));
					//}
					//if (angle > 30.0f && angle <= 60.0f)
					//{
					//	object1->setVelocity(glm::vec2(object1->getVelocity().x, -object1->getVelocity().y));
					//}
					//if (angle > 60.0f && angle >= 90.0f)
					//{
					//	object1->setVelocity(glm::vec2(object1->getVelocity().x, -object1->getVelocity().y));
					//}
					cout << "Bullet from the bottom left " << endl;
					object1->setVelocity(glm::vec2(-(object1->getVelocity().x + velocityX), object1->getVelocity().y + velocityY));
				}
				if (dx < 0 && dy < 0)
				{
					//if (angle >= 90.0f && angle <= 120.0f)
					//{
					//	object1->setVelocity(glm::vec2(object1->getVelocity().x, -object1->getVelocity().y));
					//}
					//if (angle > 120.0f && angle <= 150.0f)
					//{
					//	object1->setVelocity(glm::vec2(-object1->getVelocity().x, -object1->getVelocity().y));
					//}
					//if (angle > 150.0f && angle >= 180.0f)
					//{
					//	object1->setVelocity(glm::vec2(-object1->getVelocity().x, object1->getVelocity().y));
					//}
					cout << "Bullet from the bottom right" << endl;
					object1->setVelocity(glm::vec2(-(object1->getVelocity().x + velocityX), -(object1->getVelocity().y + velocityX)));
				}

				break;

			//default:
				//std::cout << "Collision with unknown type!" << std::endl;
				//break;
			}

			return true;
		}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
		return false;
	}
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}
