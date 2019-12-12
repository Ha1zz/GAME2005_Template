#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include <cmath>
#include "Scene.h"
#include "Label.h"
#include "ship.h"
#include "Planet.h"
#include "Hero.h"
#include "Villain.h"
#include "MoveState.h"
#include "Mine.h"
#include "CollisionManager.h"
#include "SoundManager.h"

#include <iostream>
using namespace std;

class StartScene : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	
private:
	/*Label* m_pStartLabel;
	Label* m_pInstructionsLabel;*/

	Ship* m_pShip;
	Planet* m_pPlanet;
	Mine* m_pMine;

	Hero* m_pHero;
	Villain* m_pVillain;

	MoveState m_moveState;

	glm::vec2 m_mousePosition;

	// ImGui utility functions
	void m_ImGuiKeyMap();
	void m_ImGuiSetStyle();
	void m_updateUI();

	// ImGui menu variables
	bool m_exitApp = false;
	bool m_displayAbout = false;
	bool m_displayUI = true;

	//Phycis Variables
	const float Deg2Rad = 0.0174532925f;
	const float Rad2Deg = 57.2957795130f;
	bool m_isGravityEnabled = false;
	float m_gravity = 9.8f;
	float m_PPM = 10.0f; // pixels per meters // original 5.0f
	float m_mass = 3.2f;


	glm::vec2 m_finalPosition = glm::vec2(0.0f, 0.0f);
	glm::vec2 m_velocity;
	//float m_velocity;
	float m_velocityX = 0.0f;
	float m_velocityY = 0.0f;
	glm::vec2 m_acceleration = glm::vec2(0.0f, 0.0f);
	glm::vec2 m_speed = glm::vec2(5.0f, 5.0f);
	float m_accelerationX = 0.0f;
	float m_forceX = 0.4f;


	float m_massBall = 3.2f;
	glm::vec2 m_finalPositionBall = glm::vec2(0.0f, 0.0f);
	float m_velocityMaxBall = 0.0f;
	float m_velocityBall = 0.0f;
	float m_velocityXBall = 0.0f;
	float m_velocityYBall = 0.0f;
	glm::vec2 m_accelerationBall = glm::vec2(0.0f, 0.0f);
	//glm::vec2 m_speedBall = glm::vec2(4.0f, 4.0f);
	float m_accelerationXBall = 0.0f;
	float m_accelerationYBall = 0.0f;
	float m_forceXBall = 0.4f;
	float m_forceYBall = 0.0f;
	float m_heightMaxBall = 0.0f;
	float m_heightStopBall = 0.01;
	float m_heightTempBall = 0.0f;
	float m_heightZeroBall = 0.0f;
	float m_heightBall = 0.0f;
	float m_heightNewBall = 0.0f;

	bool isFreeFallBall = true;
	float m_timeContactBall = 0.0f;
	float m_timeLastBall = 0.0f;
	float m_timeBall = 0.0f;


	glm::vec2 velocity_vectorBall = glm::vec2(0.0f,0.0f);

	float m_time = 0.016667f;
	float m_Atime = 0.016667f; // accumulated time

	float m_angle = 14.671f;
	//Physics Functions

	void m_move();
};

#endif /* defined (__START_SCENE__) */