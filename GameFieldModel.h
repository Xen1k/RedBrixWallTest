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
	/// Удаляет из определённого ряда заданное количество элементов с заданной позиции
	/// </summary>
	void DestroyConsecutives(int row, int start, int numOfToDestroy, bool destroyHorizontal);
	/// <summary>
	/// Просеивает поле: падение кристаллов и добавление недостающих
	/// </summary>
	void SiftField();
	
	/// <summary>
	/// Проверяет, есть ли на поле подряд идущие кристаллы.
	/// Если такие есть, удаляет (только один ряд) и возваращает true. False - в противном случае.
	/// </summary>
	/// <param name="rowsCheck">Метод проверки. true - проверка по рядам, false - по столбцам </param>
	bool RemoveConsecutivesPiece(bool rowsCheck);
	/// <summary>
	/// Генерирует матрицу поля, повёрнутую против часовой стрелки на 90 градусов, для прохода по столбцам
	/// </summary>
	void GenerateRotatedMatrix();
	/// <summary>
	/// Проверяет, возможно ли игроку сделать ход (собрать комбинацию три или больше подряд) по определённой матрице (по строкам или столбцам)
	/// </summary>
	bool CheckForPossibleMoves(int** currentMatrix);
public:
	GameFieldModel();
	~GameFieldModel();

	void SetView(GameFieldView* gameFieldView);
	/// <summary>
	/// Проверяет, возможно ли игроку сделать ход (собрать комбинацию три или больше подряд)
	/// </summary>
	bool CheckForPossibleMoves();
	void Init();
	/// <summary>
	/// Производит одну связку действий - удаление и просеивание. Возвращает true, если было удаление кристаллов.
	/// </summary>
	bool Tick();
	/// <summary>
	/// Меняет местами элементы
	/// </summary>
	bool Move(std::pair<int, int> from, char direction);
	/// <summary>
	/// Мешает элементы так, чтобы был хотя бы один возможный ход
	/// </summary>
	void Mix();
	void Dump();

};

