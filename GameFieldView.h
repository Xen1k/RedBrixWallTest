#pragma once

class GameFieldModel;
class GameFieldView
{
private:
	GameFieldModel* m_gameFieldModel;
public:
	void SetModel(GameFieldModel* gameFieldModel);
	void DrawField(int** fieldMatrix, int fieldSize);
};

