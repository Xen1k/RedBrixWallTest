#include "GameFieldView.h"
#include "GameFieldModel.h"
#include <iostream>

void GameFieldView::SetModel(GameFieldModel* gameFieldModel)
{
	m_gameFieldModel = gameFieldModel;
	gameFieldModel->SetView(this);
}

void GameFieldView::DrawField(int** fieldMatrix, int fieldSize)
{
	std::cout << "\x1B[2J\x1B[H";
	std::cout << "    ";
	for (int i = 0; i < fieldSize; i++)
		std::cout << i << " ";
	std::cout << std::endl;
	std::cout << "    ";
	for (int i = 0; i < fieldSize; i++)
		std::cout << "- ";
	std::cout << std::endl;
	for (int i = 0; i < fieldSize; i++)
	{
		std::cout << i << " | ";
		for (int j = 0; j < fieldSize; j++)
			if (fieldMatrix[i][j] >= 0)
				std::cout << static_cast<char>(fieldMatrix[i][j] + 'A') << " ";
			else
				std::cout << " " << " ";
		std::cout << std::endl;
	}
}