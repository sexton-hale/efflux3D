#include "Window.h"

namespace Efflux {
	Window::Window(const std::string& title, int width, int height,
		std::unordered_map<SDL_GLattr, int> attributes)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			Logger::Message(Level::SEVERE, "Failed to initialise SDL.");
			exit(-1);
		}

		for (auto const& x : attributes) {
			SDL_GL_SetAttribute(x.first, x.second);
		}

		_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
			SDL_WINDOW_OPENGL);

		if (_window == nullptr) {
			Logger::Message(Level::SEVERE, "Failed to create window.");
			exit(-1);
		}
	}

	Window::~Window()
	{
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	void Window::Render() const
	{
		SDL_GL_SwapWindow(_window);
	}
}