#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<string>


using namespace std;


// Screen dimensions
const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL; // surface contained by window
SDL_Surface* gPNGSurface = NULL; // surface of PNG image



bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL cannot initialize. Error: " << SDL_GetError() << endl;
		success = false;
	}
	else {
		window = SDL_CreateWindow("Asteroid Bullet", 20, 20, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) cout << "Window could not be created. Error: " << SDL_GetError() << endl;
		else {
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				cout << "Could not initialize image. Error: " << SDL_GetError() << endl;
				success = false;
			}
			else {
				screenSurface = SDL_GetWindowSurface(window);
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;

	gPNGSurface = loadSurface("background.png");
	if (gPNGSurface == NULL)
	{
		cout << "Could not load PNG" << endl;
		success = false;
	}

	return success;
}

void close() {
	//Free loaded image
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Cannot load image. Error: " << SDL_GetError() << endl;
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			cout << "Unable to optimize image! SDL Error : " << SDL_GetError() << endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

int main(int argc, char* args[]) {
	if (!init()) {
		cout << "Could not initialize.";
	}
	else {
		if (!loadMedia()) {
			cout << "Could not load media.";
		}
		else {
			bool quit = false;
			SDL_Event e;
			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}
				SDL_BlitSurface(gPNGSurface, NULL, screenSurface, NULL);
				SDL_UpdateWindowSurface(window);
			}
		}
	}
	close();
	return 0;
}
