#include "Texture.h"

namespace Gnin {
	namespace Graphics {

		Texture::Texture(){
			_id     = -1;

			_width  = 0;
			_height = 0;
		}

		Texture::Texture(int id) {
			_id = id;
			getImageSize();
		}

		Texture::Texture(std::string filepath) {
			if (!LoadImage(filepath.c_str(), SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y))
				std::cout << "Unable to load texture \"" << filepath.c_str() << "\"" << std::endl;
		}

		Texture::~Texture()	{

		}

		/*
		Load image with SOIL to a GL texure
		And get size of the loaded texture
		*/
		bool Texture::LoadImage(const char *path, unsigned int flags) {
			// Load image
			_id = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, flags);

			/*
			If texture is loaded
			Get the height and width
			*/
			if (_id > 0) {
				getImageSize();
				return true;
			}

			// Unable to load image
			return false;
		}

		void Texture::getImageSize() {
			/*
			If texture is loaded
			Get the height and width
			*/
			if (_id > 0) {
				int miplevel = 0;
				glBindTexture(GL_TEXTURE_2D, _id);
				glGetTexLevelParameterfv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &_width);
				glGetTexLevelParameterfv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &_height);

				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			}
		}


	}
}
