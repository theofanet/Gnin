#ifndef GNIN_GRAPHICS_TEXTURE
#define GNIN_GRAPHICS_TEXTURE

#include <iostream>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "SOIL/SOIL.h"

namespace Gnin {
	namespace Graphics {

		class Texture {
		public:
			Texture();
			Texture(int id);
			Texture(std::string filepath);
			~Texture();

			/*
			Getters for texture data
			*/
			inline GLuint getId() { return _id; }
			inline float getWidth() { return _width; }
			inline float getHeight() { return _height; }

		private:
			// Loading image private function
			bool LoadImage(const char *path, unsigned int flags = -1);
			// Size update after image load
			void getImageSize();

			GLuint _id;
			float _width, _height;
		};

	}
}

#endif // GNIN_GRAPHICS_TEXTURE
