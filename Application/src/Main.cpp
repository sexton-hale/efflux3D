#include <Core/Logger.h>
#include <Core/Renderer.h>

#include <iostream>

bool running = true;

void Print(std::string&& message) {
	std::cout << message << "\n";
}

void Update(SDL_Event e) {
	switch (e.type) 
	{
		case SDL_QUIT: {
			running = false;
			break;
		}
	}
}

void Render() {

}

int main() {
	Efflux::Logger::Init(Print);

	Efflux::Renderer context( { "Hello world!", 1280, 720 });
	
	context.Loop(running, Update, Render);
}