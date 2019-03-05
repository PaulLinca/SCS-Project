#pragma once //causes the file to be included only once in a single compilation
#include <string>
#include <SDL.h>

class Window
{
public:
	//constructo
	Window(const std::string &title, int width, int height);
	//destructor
	~Window();

	//checks if any action was performed
	void pollEvents();
	//draws on the window
	void clear(int x1, int y1, int x2, int y2) const;

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
};