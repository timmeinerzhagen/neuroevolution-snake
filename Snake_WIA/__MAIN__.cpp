// Snake_WIA.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Trainer.h"
#include "SnakeControllerPlayer.h"


int main()
{
	int width = 20, heigth = 20, ammountHiddenLayers = 4;

	//while (true) {
	//	SnakeControllerPlayer* controller = new SnakeControllerPlayer(width, heigth, -10);
	//	controller->Run();
	//}

	Trainer trainer = Trainer();
	trainer.train(50, 80, width, heigth, ammountHiddenLayers);


	//delete controller;
	getchar();
    return 0;
}

