#ifndef GNIN_GAME_MAP
#define GNIN_GAME_MAP

#include <vector>
#include <map>
#include <sstream>

#include "Tinyxml/tinyxml2.h"
#include "../Graphics/Tileset.h"
#include "../Physics/World.h"


namespace Gnin {
	namespace Game {

		struct Tile {
			Tile(int id = 0, int tilesetId = -1, GPos pos = GPos()) : id(id), tilesetId(tilesetId), position(pos) { }

			int id;
			int tilesetId;
			GPos position;
		};

		class Map{
		public:
			Map();
			~Map();

			void load(std::string mapName, Physics::World *world);

			virtual void update(float elapsedTime);
			virtual void draw();

			inline GPos getSpawnPoint() { return _spawnPoint; }

		private:
			std::vector<Graphics::Tileset> _tilesets;
			std::vector<std::vector<Tile>> _layers;

			GPos _spawnPoint;

			GSize _size, _tileSize;
		};

	}
}

#endif // GNIN_GAME_MAP