#pragma once

#include <Export.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <string>
#include <unordered_map>

#include "Logger.h"

namespace Efflux {
	class EAPI Window
	{
	public:
		Window(const std::string& title, int width, int height,
			std::unordered_map<SDL_GLattr, int> attributes);
		~Window();

		void Render() const;
	private:
		SDL_Window* _window;
	};
}