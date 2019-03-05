#include <iostream>
#include <SDL.h>
#include "Window.h"
#include <fstream>

using namespace std;

//input file
ifstream inputFile("input.txt");

//coordinates of the line
int xa[100], ya[100], xb[100], yb[100];
int numberOfLines = 0;

//this function initializes the SDL 2.0 library and displays a message whether it was successful
void initializeSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cerr << "SDL failed to initialize\n";
	}
	else
	{
		cout << "Success\n";
	}
}

//reads the coordinates of the lines that have to be rendered
void readFile()
{
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			inputFile >> xa[numberOfLines];
			inputFile >> ya[numberOfLines];
			inputFile >> xb[numberOfLines];
			inputFile >> yb[numberOfLines];
			numberOfLines++;
		}
	}

	inputFile.close();
}

int main(int argc, char **args) 
{
	//initialize SDL library
	initializeSDL();

	//create a window
	Window window("Test", 800, 600);

	//reads line coordinates from file
	readFile();

	//program loop
	while (!window.isClosed())			//if the window is open
	{
		//draw background
		window.drawBackground();

		//draw lines
		for (int i = 0; i <= numberOfLines; i++)
		{
			window.drawLine(xa[i], ya[i], xb[i], yb[i]);
		}

		//renders elements
		window.renderPresentCall();

		//check for events
		window.pollEvents();			
	}

	//cleans up all initialized subsystems
	SDL_Quit();

	return 0;
}