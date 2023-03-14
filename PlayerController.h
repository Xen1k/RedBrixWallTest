#pragma once
#include "GameFieldModel.h"

class PlayerController
{
private:
	GameFieldModel* m_model;
public:
	PlayerController(GameFieldModel* model);
	bool HandleInputAndMove();
};

