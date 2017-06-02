#ifndef GNIN_GRAPHICS_SPRITE
#define GNIN_GRAPHICS_SPRITE

#include <iostream>
#include "GL/glew.h"
#include "Texture.h"
#include "Gnin/Physics/Physics.h"
#include "Mesh.h"
#include "Shader.h"


namespace Gnin {
	namespace Graphics {

		/*
		Animation structure
		*/
		struct Animation {
			Animation(){ }

			Animation(int nbFrame, GPos pos, GSize size, float frequence = 100.0f) 
				: nbFrame(nbFrame), start(pos), size(size), frequence(frequence) {
				frame = 0;
				once = false;
                stop = false;
				elapsedTime = 0.0f;
			}

			void update(float et) {
				elapsedTime += et;
				if (elapsedTime > frequence) {
					elapsedTime -= frequence;
                    if(!stop){
                        if (frame < nbFrame - 1)
                            frame++;
                        else{
                            if(once){
                                stop = true;
                                frame = nbFrame - 1;
                            }
                            else
                                frame = 0;
                        }
                    }
				}
			}

			void getTexCoord(GSize textureSize, GVector &coord) {
                coord.x = (start.x + (frame * size.w)) / textureSize.w;
                coord.y = start.y / textureSize.h;
			}

            bool stop;
			bool once;
			int frame;
			int nbFrame;
			float frequence;
			float elapsedTime;
			GPos start;
			GSize size;
		};

        class Sprite;

        class SpriteDelgate{
        public:
            virtual void animationEnded(Sprite *sprite, std::string animation){}
        };

		/*
		Sprite class
		*/
		class Sprite {
		public:
			Sprite();
			Sprite(std::string filepath, GPos pos = GPos(), std::string shaderFile = "Assets/Shaders/BaseShader");
			~Sprite();

			/*
			Update and draw functions
			*/
			void update(float elpasedTime);
			void draw();

			// Draw size setter
			void setDrawSize(GSize s, bool cutTexture = false);

			/*
			Positions functions
			*/
			inline GPos getPosition() { return _position; }
			inline void setPosition(GPos pos) { _position = pos; }
			inline void setPositionX(float x) { _position.x = x; }
			inline void setPositionY(float y) { _position.y = y; }

			/*
			Animations functions
			*/
			void addAnimation(std::string name, int nbFrame, GPos start, GSize size, float frequence = 100.0f);
			void playAnimation(std::string name, bool once = false);

			/*
			Flip axis functions
			*/
			inline void flipX(bool f = true) { _flipX = f; }
			inline void flipY(bool f = true) { _flipY = f; }

            /*
             * Delagate function
             */
            inline void setDelegate(SpriteDelgate *d){ _delegate = d; }

		private:
			Texture _texture;
			GPos    _position;
			GSize   _drawSize;

			bool _flipX;
			bool _flipY;

			Mesh *_mesh;
			Shader *_shader;

			std::string _activeAnimation;

            SpriteDelgate *_delegate;

			std::map<std::string, Animation> _animations;
		};

	}
}

#endif // GNIN_GRAPHICS_SPRITE