#pragma once

#include <Export.h>
#include <glad/glad.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <unordered_map>
#include <functional>
#include <memory>

#include "Core/Logger.h"

#include "Window.h"

// We don't need this but I'll keep it here anyways...
typedef Efflux::Window _Window_Type;

namespace Efflux {
	struct ONLYFILE _RGLContext
	{
		std::unordered_map<SDL_GLattr, int> _attributes;
		SDL_GLprofile _profile;
		SDL_WindowFlags _flag;
		SDL_GLContext _context;
		
		_RGLContext() 
			: _profile(SDL_GL_CONTEXT_PROFILE_CORE), _flag(SDL_WINDOW_OPENGL) {
			// Make sure it is in the this order.
			_attributes[SDL_GL_CONTEXT_MAJOR_VERSION] = 3;
			_attributes[SDL_GL_CONTEXT_MINOR_VERSION] = 3;
			_attributes[SDL_GL_CONTEXT_PROFILE_MASK] = SDL_GL_CONTEXT_PROFILE_CORE;
		}
		_RGLContext(std::unordered_map<SDL_GLattr, int> attributes, SDL_GLprofile profile, SDL_WindowFlags flag)
			: _attributes(attributes), _profile(profile), _flag(flag) {}
		// not really, it actually creates the context used in SDL. 
		void AttachToWindow(SDL_Window* window) {
			_context = SDL_GL_CreateContext(window);
			SDL_GL_MakeCurrent(window, _context);
			if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
				Logger::Message(Level::ERRORMSG, "Failed to initialise GLAD.");
			}
		}
		// not really, it destroys the context
		void DettachFromWindow(SDL_Window* window) {
			SDL_GL_DeleteContext(_context);
		}
	};
	
	// In honor of Blitz3D...
	struct Graphics3D
	{
		std::string name;
	
		// x,y is not needed because at the final release the window will be completely full screen.
	
		int width;
		int height;
	};
	
	/*
		* The renderer controls your window. Didn't know that, did you? HAHAHAAHAHAHAAAA... Erm.. Lemme do my homework..
	*/
	class Renderer
	{
	private:
		std::unique_ptr<_RGLContext> _context;
		std::unique_ptr<_Window_Type> _window;
	public:
		Renderer(Graphics3D data) {
			_context = std::make_unique<_RGLContext>(_RGLContext());
			_window = std::make_unique<_Window_Type>(data.name, data.width, data.height, _context->_attributes);
		}

		~Renderer() {
			SDL_GL_DeleteContext(_context->_context);
		}
	
		// * Also I think that first param name joke comes back at me, cuz I made the engine--which controls the back-end stuff.
		void Loop(bool& isYourBeefyApplicationStillRunning,
			std::function<void(SDL_Event e)> updateFn, std::function<void()> renderFn) {
			while (isYourBeefyApplicationStillRunning)
			{
				SDL_Event e;
				if (SDL_PollEvent(&e)) 
				{
					updateFn(e);
				}
	
				renderFn();
			}
		}
		
		/*
		* By `all buffers`, I mean the color buffers we need.
		* And also, I'm leaving the clear color to black because the player won't see it anyways.
		*/
		void ClearAllBuffers() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	
		// We need indirectly swap the buffers.
		void SwapBuffers() const {
			_window->Render();
		}
	};
}