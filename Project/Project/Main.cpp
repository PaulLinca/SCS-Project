#include <iostream>
#include <SDL.h>
#include "Window.h"
#include <fstream>

using namespace std;

//input file
ifstream inputFile("input.txt");

//coordinates of the line
int xa, ya, xb, yb;

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

//reads the four coordinates that represent a line from the text file
void readFile()
{
	if (inputFile.is_open())
	{
		inputFile >> xa;
		inputFile >> ya;
		inputFile >> xb;
		inputFile >> yb;
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
		window.clear(xa, ya, xb, yb);	//render on window
		window.pollEvents();			//check if any event occurs

	}

	//cleans up all initialized subsystems
	SDL_Quit();

	return 0;
}