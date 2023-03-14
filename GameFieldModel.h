#pragma once
#include "GameFieldView.h"
#include <utility>

class GameFieldModel
{
private:
	int** m_fieldMatrix;
	int** m_rotatedFieldMatrix;
	const int m_numOfCrystalTypes = 6;
	GameFieldView* m_gameFieldView;
	const int m_fieldSize = 10;

	/// <summary>
	/// ������� �� ������������ ���� �������� ���������� ��������� � �������� �������
	/// </summary>
	void DestroyConsecutives(int row, int start, int numOfToDestroy, bool destroyHorizontal);
	/// <summary>
	/// ���������� ����: ������� ���������� � ���������� �����������
	/// </summary>
	void SiftField();
	
	/// <summary>
	/// ���������, ���� �� �� ���� ������ ������ ���������.
	/// ���� ����� ����, ������� (������ ���� ���) � ����������� true. False - � ��������� ������.
	/// </summary>
	/// <param name="rowsCheck">����� ��������. true - �������� �� �����, false - �� �������� </param>
	bool RemoveConsecutivesPiece(bool rowsCheck);
	/// <summary>
	/// ���������� ������� ����, ��������� ������ ������� ������� �� 90 ��������, ��� ������� �� ��������
	/// </summary>
	void GenerateRotatedMatrix();
	/// <summary>
	/// ���������, �������� �� ������ ������� ��� (������� ���������� ��� ��� ������ ������) �� ����������� ������� (�� ������� ��� ��������)
	/// </summary>
	bool CheckForPossibleMoves(int** currentMatrix);
public:
	GameFieldModel();
	~GameFieldModel();

	void SetView(GameFieldView* gameFieldView);
	/// <summary>
	/// ���������, �������� �� ������ ������� ��� (������� ���������� ��� ��� ������ ������)
	/// </summary>
	bool CheckForPossibleMoves();
	void Init();
	/// <summary>
	/// ���������� ���� ������ �������� - �������� � �����������. ���������� true, ���� ���� �������� ����������.
	/// </summary>
	bool Tick();
	/// <summary>
	/// ������ ������� ��������
	/// </summary>
	bool Move(std::pair<int, int> from, char direction);
	/// <summary>
	/// ������ �������� ���, ����� ��� ���� �� ���� ��������� ���
	/// </summary>
	void Mix();
	void Dump();

};

