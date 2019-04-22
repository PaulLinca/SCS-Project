#pragma once //causes the file to be included only once in a single compilation
#include <string>
#include <SDL.h>
#include "myStruct.h"

class Window
{
public:
	//constructo
	Window(const std::string &title, int width, int height);
	//destructor
	~Window();

	//checks if any action was performed
	void pollEvents();
	//draws background
	void drawBackground() const;
	//actually renders the items
	void renderPresentCall();

	//draws lines on window
	void drawLine(Line line);
	int getOctant(Line line);
	//draws a circle
	void drawCircle(Circle circle);

	//checks if window is closed
	inline bool isClosed() const { return _closed; }

private:
	bool init();

private:
	//window properties
	std::string _title;
	int _width = 800;
	int _height = 600;

	//is window closed or not
	bool _closed = false;

	//initialize with nullptr
	SDL_Window *_window = nullptr;
	SDL_Renderer *_renderer = nullptr;

	//speed at which the points are drawn
	long _drawSpeed;
};