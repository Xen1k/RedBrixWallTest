#include "GameFieldModel.h"
#include <iostream>
#include <algorithm>
#include <random>

GameFieldModel::GameFieldModel()
{
	m_fieldMatrix = new int*[m_fieldSize];
	for (int i = 0; i < m_fieldSize; i++)
		m_fieldMatrix[i] = new int[m_fieldSize];

	m_rotatedFieldMatrix = new int* [m_fieldSize];
	for (int i = 0; i < m_fieldSize; i++)
		m_rotatedFieldMatrix[i] = new int[m_fieldSize];
}

void GameFieldModel::Init()
{
	for (int i = 0; i < m_fieldSize; i++)
		for (int j = 0; j < m_fieldSize; j++)
			m_fieldMatrix[i][j] = rand() % m_numOfCrystalTypes;
	GenerateRotatedMatrix();
} 

void GameFieldModel::GenerateRotatedMatrix()
{
	for (int i = 0; i < m_fieldSize; i++)
		for (int j = 0; j < m_fieldSize; j++)
			m_rotatedFieldMatrix[i][j] = m_fieldMatrix[j][m_fieldSize - i - 1];
}

bool GameFieldModel::CheckForPossibleMoves(int** currentMatrix)
{
	for (int i = 0; i < m_fieldSize; i++)
	{
		for (int j = 0; j < m_fieldSize; j++)
		{
			// Если равны два подряд идущих символа
			if (currentMatrix[i][j] == currentMatrix[i][j + 1])
			{
				if ((j >= 2 && // Если слева есть место для перемещения 
						((i > 0 && currentMatrix[i - 1][j - 2] == currentMatrix[i][j]) || // Если сверху есть место для перемещения и будут подряд идущие кристалы при замене
						(i < m_fieldSize - 1 && currentMatrix[i + 1][j - 2] == currentMatrix[i][j]))) // Если снизу есть место для перемещения 
					|| 
					(j < m_fieldSize - 1 && // Если справа есть место для перемещения 
						((i > 0 && currentMatrix[i - 1][j + 1] == currentMatrix[i][j]) || // Если сверху есть место для перемещения и будут подряд идущие кристалы при замене
						(i < m_fieldSize - 1 && currentMatrix[i + 1][j + 1] == currentMatrix[i][j])))) // Если снизу есть место для перемещения 
					return true;
			}
		}
	}
	return false;
}

bool GameFieldModel::CheckForPossibleMoves()
{
	if (CheckForPossibleMoves(m_fieldMatrix) || CheckForPossibleMoves(m_rotatedFieldMatrix))
		return true;
	return false;
}



void GameFieldModel::DestroyConsecutives(int row, int start, int numOfToDestroy, bool destroyHorizontal)
{
	for (int i = start; i < start + numOfToDestroy; i++)
		m_fieldMatrix[destroyHorizontal ? row : i][destroyHorizontal ? i : row] = -1;
}

void GameFieldModel::SiftField()
{
	bool siftPerfomed = false;
	// Замена пустых место верхнего ряда
	for (int i = 0; i < m_fieldSize; i++)
		if (m_fieldMatrix[0][i] == -1)
			m_fieldMatrix[0][i] = rand() % m_numOfCrystalTypes;
	// Падение кристаллов на пустые места
	for (int i = 1; i < m_fieldSize; i++)
	{
		for (int j = 0; j < m_fieldSize; j++)
		{
			if (m_fieldMatrix[i][j] == -1)
			{
				std::swap(m_fieldMatrix[i][j], m_fieldMatrix[i - 1][j]);
				siftPerfomed = true;
			}
		}
	}
	if (siftPerfomed)
		SiftField();
}

bool GameFieldModel::RemoveConsecutivesPiece(bool rowsCheck)
{
	GenerateRotatedMatrix();
	int lastCheckedCrystal;
	int numOfConsecutives = 1;
	const int minConsecutivesToDestroy = 3;
	bool lastCheckedInitialized = false;
	for (int i = 0; i < m_fieldSize; i++)
	{
		for (int j = 0; j < m_fieldSize; j++)
		{
			// Элемент матрицы, проверяемый в данный момент
			int currentMatrixElement = rowsCheck ? m_fieldMatrix[i][j] : m_fieldMatrix[j][i];
			if (!lastCheckedInitialized)
			{
				lastCheckedCrystal = currentMatrixElement;
				lastCheckedInitialized = true;
				continue;
			}
			if (lastCheckedCrystal != currentMatrixElement)
			{
				// Destroy consecutives
				if (numOfConsecutives >= minConsecutivesToDestroy)
				{
					DestroyConsecutives(i, j - numOfConsecutives, numOfConsecutives, rowsCheck);
					return true;
				}
				lastCheckedCrystal = currentMatrixElement;
				numOfConsecutives = 1;
				continue;
			}
			numOfConsecutives++;

		}
		if (numOfConsecutives >= minConsecutivesToDestroy)
		{
			DestroyConsecutives(i, m_fieldSize - numOfConsecutives, numOfConsecutives, rowsCheck);
			return true;
		}
		numOfConsecutives = 1;
		lastCheckedInitialized = false;
	}
	return false;
}


bool GameFieldModel::Tick()
{
	if (RemoveConsecutivesPiece(false) || RemoveConsecutivesPiece(true))
	{
		SiftField();
		return true;
	}
	return false;
}

bool GameFieldModel::Move(std::pair<int, int> from, char direction)
{
	std::pair<int, int> targetSwapPosition;
	switch (direction)
	{
		case 'l':
		{
			if (from.first <= 0)
				return false;
			targetSwapPosition = std::make_pair(from.second, from.first - 1);
			break;
		}
		case 'r':
		{
			if (from.first >= m_fieldSize - 1)
				return false;
			targetSwapPosition = std::make_pair(from.second, from.first + 1);
			break;
		}
		case 'u':
		{
			if (from.second <= 0)
				return false;
			targetSwapPosition = std::make_pair(from.second - 1, from.first);
			break;
		}
		case 'd':
		{
			if (from.second >= m_fieldSize - 1)
				return false;
			targetSwapPosition = std::make_pair(from.second + 1, from.first);
			break;
		}
		default:
		{
			return false;
		}
	}
	std::swap(m_fieldMatrix[from.second][from.first], m_fieldMatrix[targetSwapPosition.first][targetSwapPosition.second]);
	if (Tick()) // Если ход возможен
		return true;
	std::swap(m_fieldMatrix[from.second][from.first], m_fieldMatrix[targetSwapPosition.first][targetSwapPosition.second]);
	return false;
}



void GameFieldModel::Mix()
{
	for (int i = 0; i < m_fieldSize; i++)
		std::random_shuffle(&m_fieldMatrix[i][0], &m_fieldMatrix[i][m_fieldSize - 1]);
	while (Tick()); //  Удаление готовых троек
	int i = rand() % (m_fieldSize - 2);
	int j = rand() % (m_fieldSize - 1);
	int crystalNum = 127;// rand() % m_numOfCrystalTypes;
	m_fieldMatrix[i][j] = crystalNum;
	m_fieldMatrix[i + 1][j] = crystalNum;
	m_fieldMatrix[i + 2][j + 1] = crystalNum;
	GenerateRotatedMatrix();
}

void GameFieldModel::Dump()
{
	m_gameFieldView->DrawField(m_fieldMatrix, m_fieldSize);
}

void GameFieldModel::SetView(GameFieldView* gameFieldView)
{
	m_gameFieldView = gameFieldView;
}

GameFieldModel::~GameFieldModel()
{
	for (int i = 0; i < m_fieldSize; i++) 
		delete[] m_fieldMatrix[i];
	delete[] m_fieldMatrix;
}
