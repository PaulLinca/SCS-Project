#include "Window.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "myStruct.h"
#include "Timer.h"

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

//Detects in which octant a line is situated
int Window::getOctant(Line line)
{
	int deltaY = (line.endY - line.startY);
	int deltaX = (line.endX - line.startX);
	//Slope		
	float m = abs(deltaY) / (float)abs(deltaX);

	if ((m < 1) && (deltaX > 0) && (deltaY <= 0)) //first octant
		return 1;

	if ((m >= 1) && (deltaX > 0) && (deltaY <= 0)) //second octant
		return 2;

	if ((m >= 1) && (deltaX <0) && (deltaY <= 0)) //third octant
		return 3;

	if ((m < 1) && (deltaX < 0) && (deltaY <= 0))//fourth octant
		return 4;

	if ((m < 1) && (deltaX < 0) && (deltaY >= 0))//fifth octant
		return 5;

	if ((m >= 1) && (deltaX < 0) && (deltaY >= 0)) //sixth octant
		return 6;

	if ((m >= 1) && (deltaX > 0) && (deltaY >= 0)) //seventh octant
		return 7;

	if ((m < 1) && (deltaX > 0) && (deltaY >= 0)) //eight octant
		return 8;

	return 0;
}

//draws a line using Bresenham's algorithm
void Window::drawLine(Line line)
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);	//set color to white

	int tmpStartX = 0;
	int tmpStartY = 0;
	int tmpEndX = 0;
	int tmpEndY = 0;
	int tmpCurrentX = 0;
	int tmpCurrentY = 0;

	int dy = abs(line.endY - line.startY);
	int dx = abs(line.endX - line.startX);

	int d, inc1, inc2;

	int octant = getOctant(line);

	switch (octant)
	{
	case 1:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX < tmpEndX)
		{
			//Draw current point
			SDL_RenderDrawPoint(_renderer, tmpCurrentX, tmpCurrentY);
			SDL_RenderPresent(_renderer);
			Wait(_drawSpeed);

			++tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentY;
			}
		}
		break;
	case 2:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY > tmpEndY)
		{
			//Draw current point
			SDL_RenderDrawPoint(_renderer, tmpCurrentX, tmpCurrentY);
			SDL_RenderPresent(_renderer);
			Wait(_drawSpeed); 

			--tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentX;
			}
		}
		break;
	case 3:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY > tmpEndY)
		{
			//Draw current point
			SDL_RenderDrawPoint(_renderer, tmpCurrentX, tmpCurrentY);
			SDL_RenderPresent(_renderer);
			Wait(_drawSpeed);

			--tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentX;
			}
		}
		break;
	case 4:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX > tmpEndX)
		{
			//Draw current point
			SDL_RenderDrawPoint(_renderer, tmpCurrentX, tmpCurrentY);
			SDL_RenderPresent(_renderer);
			Wait(_drawSpeed);

			--tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentY;
			}
		}
		break;
	case 5:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX > tmpEndX)
		{
			//Draw current point
			SDL_RenderDrawPoint(_renderer, tmpCurrentX, tmpCurrentY);
			SDL_RenderPresent(_renderer);
			Wait(_drawSpeed);

			--tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentY;
			}
		}
		break;
	case 6:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY < tmpEndY)
		{
			//Draw current point
			SDL_RenderDrawPoint(_renderer, tmpCurrentX, tmpCurrentY);
			SDL_RenderPresent(_renderer);
			Wait(_drawSpeed);

			++tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentX;
			}
		}

		break;
	case 7:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY < tmpEndY)
		{
			//Draw current point
			SDL_RenderDrawPoint(_renderer, tmpCurrentX, tmpCurrentY);
			SDL_RenderPresent(_renderer);
			Wait(_drawSpeed);

			++tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentX;
			}
		}
		break;
	case 8:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX < tmpEndX)
		{
			//Draw current point
			SDL_RenderDrawPoint(_renderer, tmpCurrentX, tmpCurrentY);
			SDL_RenderPresent(_renderer);
			Wait(_drawSpeed);
			++tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentY;
			}
		}
		break;

	default:
		cout << "Vertical line\n";
		SDL_RenderDrawLine(_renderer, line.startX, line.startY, line.endX, line.endY);			//draws line with given parameters
		break;
	}
}

//fills background with the color blue
void Window::drawBackground() const
{
	//draw background
	SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);		//set color of the renderer to blue
	SDL_RenderClear(_renderer);								//gets the color on the renderer
}

//reverses an array
void rvereseArray(int arr[], int start, int end)
{
	while (start < end)
	{
		int temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
		start++;
		end--;
	}
}

//draws a circle
void Window::drawCircle(Circle circle)
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	int x0 = circle.midX;
	int y0 = circle.midY;
	int radius = circle.radius;

	int x = radius;
	int y = 0;
	int err = 0;

	int x1[10000], x2[10000], x3[10000], x4[10000], x5[10000], x6[10000], x7[10000], x8[10000];
	int y1[10000], y2[10000], y3[10000], y4[10000], y5[10000], y6[10000], y7[10000], y8[10000];

	int n = 0;
	while (x >= y)
	{
		x1[n] = x0 + x;
		y1[n] = y0 + y;

		x2[n] = x0 + y;
		y2[n] = y0 + x;

		x3[n] = x0 - y;
		y3[n] = y0 + x;

		x4[n] = x0 - x;
		y4[n] = y0 + y;

		x5[n] = x0 - x;
		y5[n] = y0 - y;

		x6[n] = x0 - y;
		y6[n] = y0 - x;

		x7[n] = x0 + y;
		y7[n] = y0 - x;

		x8[n] = x0 + x;
		y8[n] = y0 - y;

		n++;

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}

	for (int i = 0; i < n; i++)
	{
		SDL_RenderDrawPoint(_renderer, x1[i], y1[i]);
		SDL_RenderPresent(_renderer);
		Wait(_drawSpeed);
	}

	rvereseArray(x2, 0, n - 1);
	rvereseArray(y2, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		SDL_RenderDrawPoint(_renderer, x2[i], y2[i]);
		SDL_RenderPresent(_renderer);
		Wait(_drawSpeed);
	}

	for (int i = 0; i < n; i++)
	{
		SDL_RenderDrawPoint(_renderer, x3[i], y3[i]);
		SDL_RenderPresent(_renderer);
		Wait(_drawSpeed);
	}

	rvereseArray(x4, 0, n - 1);
	rvereseArray(y4, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		SDL_RenderDrawPoint(_renderer, x4[i], y4[i]);
		SDL_RenderPresent(_renderer);
		Wait(_drawSpeed);
	}

	for (int i = 0; i < n; i++)
	{
		SDL_RenderDrawPoint(_renderer, x5[i], y5[i]);
		SDL_RenderPresent(_renderer);
		Wait(_drawSpeed);
	}

	rvereseArray(x6, 0, n - 1);
	rvereseArray(y6, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		SDL_RenderDrawPoint(_renderer, x6[i], y6[i]);
		SDL_RenderPresent(_renderer);
		Wait(_drawSpeed);
	}

	for (int i = 0; i < n; i++)
	{
		SDL_RenderDrawPoint(_renderer, x7[i], y7[i]);
		SDL_RenderPresent(_renderer);
		Wait(_drawSpeed);
	}

	rvereseArray(x8, 0, n - 1);
	rvereseArray(y8, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		SDL_RenderDrawPoint(_renderer, x8[i], y8[i]);
		SDL_RenderPresent(_renderer);
		Wait(_drawSpeed);
	}
}

//render the elements on screen
void Window::renderPresentCall()
{
	SDL_RenderPresent(_renderer);
}