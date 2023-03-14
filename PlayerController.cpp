#include "PlayerController.h"
#include <iostream>

PlayerController::PlayerController(GameFieldModel* model)
{
	m_model = model;
}

bool PlayerController::HandleInputAndMove()
{
	char option;
	int xCoord, yCoord;
	char direction;
	for (;;)
	{
		std::cout << std::endl;
		std::cout << "Input: (\"m x y d\" or \"q\" to quit)" << std::endl << "> ";
		std::cin >> option;
		if (option == 'q')
		{
			return false;
		}
		else if (option == 'm')
		{
			std::cin >> xCoord >> yCoord >> direction;
			std::cin.ignore(10000, '\n');
			if (!m_model->Move(std::make_pair(xCoord, yCoord), direction))
			{
				std::cout << "This move is impossible!" << std::endl;
				system("pause");
				m_model->Dump();
				continue;
			}
			return true;
		}
		std::cin.ignore(10000, '\n');
		std::cout << "Wrong option!" << std::endl;
		system("pause");
		m_model->Dump();
	}
}