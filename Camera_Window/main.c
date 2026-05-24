#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// Got a camera of 1280x720 and FPS 30
/// </summary>
typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_CameraID* devices;
	SDL_Camera* camera;
	SDL_Texture* texture;
	int width;
	int height;
	int camera_count;
} AppState;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
	AppState* app_state = malloc(sizeof(AppState));
	*app_state = (AppState){
		.width = 800,
		.height = 600
	};
	*appstate = app_state;

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_CAMERA)) {
		SDL_Log("couldnt initiliaze SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if (!SDL_CreateWindowAndRenderer("SDL3 Camera Demo", app_state->width, app_state->height, 0, &(app_state->window), &(app_state->renderer))) {
		SDL_Log("couldnt create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;

	}

	SDL_CameraID* devices = SDL_GetCameras(&app_state->camera_count);
	if (devices == NULL || app_state->camera_count == 0) {
		SDL_Log("Cant enumerate available devices or no camera is attached: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	app_state->devices = devices;

	SDL_Log("Found %d cameras!", app_state->camera_count);

	// open first camera
	app_state->camera = SDL_OpenCamera(devices[0], NULL);
	if (app_state->camera == NULL) {
		SDL_Log("Cant open the selected camera %s.", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// get the selected camera format
	SDL_CameraSpec spec;
	SDL_GetCameraFormat(app_state->camera, &spec);
	int FPS = spec.framerate_numerator / spec.framerate_denominator;
	SDL_Log("Got a camera of %dx%d and FPS %d", spec.width, spec.height, FPS);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	AppState* app_state = appstate;

	SDL_Surface *frame = SDL_AcquireCameraFrame(app_state->camera, NULL);

	if (frame != NULL) {

		if (app_state->texture == NULL) {

			//SDL_SetWindowSize(app_state->window, 300, 300);
			SDL_SetWindowSize(app_state->window, frame->w, frame->h); // sets window size for camera window
			app_state->width = frame->w;
			app_state->height = frame->h;

			app_state->texture = SDL_CreateTexture(app_state->renderer, frame->format, SDL_TEXTUREACCESS_STREAMING, frame->w, frame->h);
		}
		else {
			SDL_UpdateTexture(app_state->texture, NULL, frame->pixels, frame->pitch);
		}

		SDL_ReleaseCameraFrame(app_state->camera, frame);
	}

	SDL_SetRenderDrawColorFloat(app_state->renderer, 0.4f, 0.6f, 1.0f, SDL_ALPHA_OPAQUE_FLOAT);
	SDL_RenderClear(app_state->renderer);

	if (app_state->texture) {
		SDL_RenderTexture(app_state->renderer, app_state->texture, NULL, NULL);
	}

	SDL_RenderPresent(app_state->renderer);
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	AppState* app_state = appstate;
	if (app_state->devices != NULL) {
		SDL_free(app_state->devices);
	}
	if (app_state->camera != NULL) {
		SDL_CloseCamera(app_state->camera);
	}
	if (app_state->texture != NULL) {
		SDL_DestroyTexture(app_state->texture);
	}
	free(app_state);
}