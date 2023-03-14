#include <iostream>
#include <ctime>
#include "GameFieldView.h"
#include "GameFieldModel.h"
#include "PlayerController.h"
#include <thread>
#include <chrono>

int main()
{
    srand(time(0));
    GameFieldView* gameFieldView = new GameFieldView();
    GameFieldModel* gameFieldModel = new GameFieldModel();
    PlayerController* playerController = new PlayerController(gameFieldModel);
    gameFieldView->SetModel(gameFieldModel);
    gameFieldModel->Init();
    do
    {
        if (!gameFieldModel->CheckForPossibleMoves())
            gameFieldModel->Mix();
        gameFieldModel->Dump();
        while (gameFieldModel->Tick())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            gameFieldModel->Dump();
        }
    } while (playerController->HandleInputAndMove());

    return 0;
}

