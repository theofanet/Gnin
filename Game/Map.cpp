#include "Map.h"

#include "../Gnin.h"

using namespace tinyxml2;

namespace Gnin {
	namespace Game {

		Map::Map() {
		}


		Map::~Map(){
		}

		void Map::update(float elapsedTime) {

		}

		void Map::draw() {
			/*
			Draw tiles layers
			*/
			for (std::vector<std::vector<Tile>>::iterator it = _layers.begin(); it != _layers.end(); ++it) {
				for (std::vector<Tile>::iterator tit = (*it).begin(); tit != (*it).end(); ++tit) {
					_tilesets[(*tit).tilesetId].drawTile((*tit).id, (*tit).position);
				}
			}
		}

		/*
		Loading map from a TMX file 
		Tiled files
		*/
		void Map::load(std::string filePath, Physics::World *world) {
			/*
			Opening XML document
			*/
			XMLDocument doc;
			doc.LoadFile(filePath.c_str());

			// Get map and tiles data
			XMLElement *mapNode = doc.FirstChildElement("map");

			float width, height;

			mapNode->QueryFloatAttribute("width", &width);
			mapNode->QueryFloatAttribute("height", &height);
			_size = GSize(width, height);

			float tileWidth, tileHeight;

			mapNode->QueryFloatAttribute("tilewidth", &tileWidth);
			mapNode->QueryFloatAttribute("tileheight", &tileHeight);
			_tileSize = GSize(tileWidth, tileHeight);

			/*
			Load tilesets
			*/
			XMLElement *tilesetNode = mapNode->FirstChildElement("tileset");

			while (tilesetNode) {
				std::stringstream ss;
				XMLElement *pImg = tilesetNode->FirstChildElement("image");
				const char *imageSrc = pImg->Attribute("source");
				std::string fp;
				ss.str(imageSrc);
				ss.clear();
				fp = ss.str();
				
				int firstGid;
				float tilesetWidth, tilesetHeight;
				tilesetNode->QueryIntAttribute("firstgid", &firstGid);
				pImg->QueryFloatAttribute("width", &tilesetWidth);
				pImg->QueryFloatAttribute("height", &tilesetHeight);

				_tilesets.push_back(Graphics::Tileset(fp, GSize(tilesetWidth, tilesetHeight), _tileSize, firstGid));

				tilesetNode = tilesetNode->NextSiblingElement("tileset");
			}

			/*
			Load tiles layers
			*/
			XMLElement *layerNode = mapNode->FirstChildElement("layer");

			while (layerNode) {
				XMLElement *dataNode = layerNode->FirstChildElement("data");

				while (dataNode) {
					const char *lines = dataNode->GetText();
					std::stringstream ss;
					ss.str(lines);
					ss.clear();
					int tileCount = 0;
					std::string token;

					std::vector<Tile> layer;
					while (std::getline(ss, token, ',')) {
						int gid = atoi(token.c_str());

						if (gid) {
							Graphics::Tileset tls;
							int closest = 0;
							int tid = -1;
							int ii = -1;

							for (std::vector<Graphics::Tileset>::iterator it = _tilesets.begin(); it != _tilesets.end(); ++it) {
								ii++;

								if ((*it).getFirstId() <= gid) {
									if ((*it).getFirstId() > closest) {
										closest = (*it).getFirstId();
										tls = (*it);
										tid = ii;
									}
								}
							}

							if (tls.getFirstId() != -1) {
								float xx = (tileCount % (int)width) * tileWidth + tileWidth / 2;
								float yy = ((height - 0.5) * tileHeight) - (tileHeight * std::floor(tileCount / width) + tileHeight / 2);
								
								layer.push_back(Tile(gid, tid, GPos(xx, yy)));
							}
						}

						tileCount++;
					}

					_layers.push_back(layer);
					dataNode = dataNode->NextSiblingElement("data");
				}

				layerNode = layerNode->NextSiblingElement("layer");
			}


			/*
			Load object groups
			*/
			XMLElement *objectgroupNode = mapNode->FirstChildElement("objectgroup");
			while (objectgroupNode) {
				const char *objectgroupName = objectgroupNode->Attribute("name");
				std::stringstream ss;
				ss << objectgroupName;

				if (ss.str() == "spawn points") {
					XMLElement *objectNode = objectgroupNode->FirstChildElement("object");
					float spx, spy;
					objectNode->QueryFloatAttribute("x", &spx);
					objectNode->QueryFloatAttribute("y", &spy);

					_spawnPoint = GPos(spx, ((height - 0.5) * tileHeight) - spy);
				}
				else if (ss.str() == "static") {
					XMLElement *pObject = objectgroupNode->FirstChildElement("object");
					while (pObject) {
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						float w = pObject->FloatAttribute("width");
						float h = pObject->FloatAttribute("height");

						Physics::Fixture *fixture = new Physics::Fixture();
						fixture->addVertex(GPoint(-w / 2, -h / 2));
						fixture->addVertex(GPoint(-w / 2, h / 2));
						fixture->addVertex(GPoint(w / 2, h / 2));
						fixture->addVertex(GPoint(w / 2, -h / 2));

						GPos pos = GPos(x + w / 2, y + h / 2);
						pos.y = ((height - 0.5) * tileHeight) - pos.y;

						world->createBody(pos, fixture, Physics::BODY_STATIC);

						pObject = pObject->NextSiblingElement("object");
					}
				}
				/*else if (ss.str() == "doors") {
					XMLElement *pObject = objectgroupNode->FirstChildElement("object");
					while (pObject) {
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						float w = pObject->FloatAttribute("width");
						float h = pObject->FloatAttribute("height");

						const char *pValue = pObject->Attribute("name");
						std::stringstream ssv;
						ssv << pValue;
						Door *door = new Door(graphics, _world, ssv.str(), GPoint(x, y) * Globals::SPRITE_SCALE, GSize(w, h) * Globals::SPRITE_SCALE);
						_doors.push_back(door);

						pObject = pObject->NextSiblingElement("object");
					}
				}*/
				/*else if (ss.str() == "enemies") {

					XMLElement *eObject = objectgroupNode->FirstChildElement("object");
					const char *eName = eObject->Attribute("name");
					std::stringstream sse;
					sse << eName;

					while (eObject) {
						if (sse.str() == "Snake") {
							float x = eObject->FloatAttribute("x") * Globals::SPRITE_SCALE;
							float y = eObject->FloatAttribute("y") * Globals::SPRITE_SCALE;
							float w = eObject->FloatAttribute("width") * Globals::SPRITE_SCALE;

							Snake *snake = new Snake(graphics, _world, GPoint(x, y));
							snake->setBoundries((x + w), x);
							_enemies.push_back(snake);
						}

						eObject = eObject->NextSiblingElement("object");
					}
				}*/
				/**
				* Other object group goes here
				* TODO : KEYS
				*/


				objectgroupNode = objectgroupNode->NextSiblingElement("objectgroup");
			}
		}

	}
}