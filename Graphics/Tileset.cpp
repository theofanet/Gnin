#include "Tileset.h"

namespace Gnin {
	namespace Graphics {

		Tileset::Tileset(std::string filepath, GSize size, GSize tileSize, int firstId){
			_texture = Texture(filepath);
			_size = size;
			_tileSize = tileSize;
			_firstId = firstId;
		}


		Tileset::~Tileset(){

		}

		void Tileset::drawTile(int id, GPos pos) {
			// Calculate tile position in texture
			int tx = (id % (int)(_size.w / _tileSize.w) - 1) * _tileSize.w;
			if (tx < 0)
				tx = _size.w - _tileSize.w;
			int ty = _size.h - std::ceil((id - _firstId) / (_size.w / _tileSize.w)) * _tileSize.h;

			// Call drawTile with texture X and Y
			drawTile(tx, ty, pos);
		}

		void Tileset::drawTile(int textureX, int textureY, GPos pos) {
			/*
			Conerting texture x and y
			to perentages min and max
			*/
			GPoint tmin;
			GPoint tmax;

			tmin.x = (textureX) / _size.w;
			tmin.y = (textureY) / _size.h;
			tmax.x = (textureX + _tileSize.w) / _size.w;
			tmax.y = (textureY + _tileSize.h) / _size.h;

			// Save Matrix
			glPushMatrix();

			// Move to position
			glTranslated(pos.x, pos.y, 0);

			// Enable texture and bind it
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _texture.getId()); 

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

			/*
			Draw quad with texture mapped
			*/
			glBegin(GL_QUADS);
			glTexCoord2f(tmin.x, tmin.y); glVertex2f(-_tileSize.w / 2, -_tileSize.h / 2);
			glTexCoord2f(tmax.x, tmin.y); glVertex2f(_tileSize.w / 2, -_tileSize.h / 2);
			glTexCoord2f(tmax.x, tmax.y); glVertex2f(_tileSize.w / 2, _tileSize.h / 2);
			glTexCoord2f(tmin.x, tmax.y); glVertex2f(-_tileSize.w / 2, _tileSize.h / 2);
			glEnd();

			// Disable texture
			glDisable(GL_TEXTURE_2D);

			// Restore Matrix
			glPopMatrix();
		}

	}
}
