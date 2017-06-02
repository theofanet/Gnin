#ifndef GNIN_GRAPHICS_TILESET
#define GNIN_GRAPHICS_TILESET

#include <string>

#include "Texture.h"
#include "../Physics/Physics.h"

namespace Gnin {
	namespace Graphics {

		class Tileset {
		public:
			Tileset() { _firstId = -1; }
			Tileset(std::string filepath, GSize size, GSize tileSize, int firstId = 1);
			~Tileset();

			void drawTile(int id, GPos position);
			void drawTile(int textureX, int textureY, GPos pos);

			int getFirstId() { return _firstId; }

		private:
			int _firstId;

			Texture _texture;

			GSize _size;
			GSize _tileSize;
		};

	}
}

#endif // GNIN_GRAPHICS_TILESET