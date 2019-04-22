#include <iostream>
#include <SDL.h>
#include "Window.h"
#include <fstream>
#include "myStruct.h"

using namespace std;

//input file
ifstream inputFile("input.txt");

Line lines[100];
int numberOfLines = 0;

Circle circles[100];
int numberOfCircles = 0;

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
			int type;
			inputFile >> type;

			if (type == 1)
			{
				inputFile >> lines[numberOfLines].startX;
				inputFile >> lines[numberOfLines].startY;
				inputFile >> lines[numberOfLines].endX;
				inputFile >> lines[numberOfLines].endY;

				numberOfLines++;
			}
			else if (type == 2)
			{
				inputFile >> circles[numberOfCircles].midX;
				inputFile >> circles[numberOfCircles].midY;
				inputFile >> circles[numberOfCircles].radius;

				numberOfCircles++;
			}
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

	//draw background
	window.drawBackground();

	//draw lines
	for (int i = 0; i < numberOfLines; i++)
	{
		window.drawLine(lines[i]);
	}

	//draw circles
	for (int i = 0; i < numberOfCircles; i++)
	{
		window.drawCircle(circles[i]);
	}

	//program loop
	while (!window.isClosed())			//if the window is open
	{
		//check for events
		window.pollEvents();

		//renders elements
		window.renderPresentCall();
	}

	//cleans up all initialized subsystems
	SDL_Quit();

	return 0;
}