#include "Window.h"
#include <iostream>

using namespace std;

/*
*	Constructor of the Window class
*	Parameters: title of the window, width of the window, height of the window
*/
Window::Window(const std::string &title, int width, int height) :
_title(title), _width(width), _height(height)
{
	_closed = !init(); 
}

//destructor of the window class
Window::~Window()
{
	SDL_DestroyRenderer(_renderer);	//destroy the renderer
	SDL_DestroyWindow(_window);		//destroy the window
	SDL_Quit();						//quit SDL 2.0
}

//initializes the window
bool Window::init()
{
	//initialize SDL for creating the window
	if (SDL_Init(SDL_INIT_VIDEO) != 0)	//init only the video portion of SDL
	{
		cerr << "Failed to initialize SDL.\n";
		return false;
	}

	//create the window 
	_window = SDL_CreateWindow(
		_title.c_str(),				//given title
		SDL_WINDOWPOS_CENTERED,		//center of the screen
		SDL_WINDOWPOS_CENTERED,
		_width, _height,			//given width and height
		0							//no flags needed
	);

	//check if the window was created successfully
	if (_window == nullptr)
	{
		cerr << "Failed to create window.\n";
		return false;
	}

	/*
	*Initialize renderer
	* -1 initializes the the rendering driver that supports the flags given in the third argument
	* SDL_RENDERER_PRESENTVSYNC caps the framerate at 60fps
	*/
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

	//checks if renderer was initialized successfully
	if (_renderer == nullptr)
	{
		cerr << "Failed to create renderer.\n";
		return false;
	}

	return true;
}

//checks if an event was performed
void Window::pollEvents()
{
	SDL_Event event;

	//tetsts if an event actually occured
	if (SDL_PollEvent(&event))
	{
		//if 'X' button is pressed
		if (event.type == SDL_QUIT)
		{
			_closed = true;
		}

		//if keyboard button is pressed
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:			//'esc' button
					_closed = true;
					break;
			}
		}
	}
}

//renders things on screen
void Window::clear(int x1, int y1, int x2, int y2) const
{
	//draw background
	SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);		//set color of the renderer to blue
	SDL_RenderClear(_renderer);								//gets the color on the renderer
	SDL_RenderPresent(_renderer);							//actually puts the color on the screen

	//draw line
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);	//set color to white
	SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);			//draws line with given parameters
	SDL_RenderPresent(_renderer);							//actually puts the line onto the screen
}