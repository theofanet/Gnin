#include "Sprite.h"


namespace Gnin {
    namespace Graphics {

        Sprite::Sprite(){
            _activeAnimation = "";
            _flipX = false;
            _flipY = false;
            _delegate = NULL;
        }

        Sprite::Sprite(std::string filepath, GPos pos, std::string shaderFile) {
            _texture  = Texture(filepath);
            _position = pos;
            _activeAnimation = "";
            _flipX = false;
            _flipY = false;
            _mesh = NULL;

            _delegate = NULL;

            setDrawSize(GSize(_texture.getWidth(), _texture.getHeight()));

            _shader = new Gnin::Graphics::Shader(shaderFile);
        }

        Sprite::~Sprite(){
            delete _mesh;
            delete _shader;
        }

        /*
        Update sprite
        */
        void Sprite::update(float elapsedTime) {
            if (_activeAnimation != ""){
                _animations[_activeAnimation].update(elapsedTime);
                if(_animations[_activeAnimation].stop && _delegate)
                    _delegate->animationEnded(this, _activeAnimation);
            }
        }

        /*
        Draw sprite to the screen
        At position
        */
        void Sprite::draw() {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, _texture.getId());

            // Save current Matrix
            glPushMatrix();

            // Translate matrix
            glTranslated(_position.x, _position.y, 0);

            // Flip image
            if (_flipX || _flipY)
                glRotated(180, (_flipX ? 1 : 0), (_flipY ? 1 : 0), 0);

            // Draw quad with texture binded
            GVector animationcoord;

            if (_activeAnimation != "")
                _animations[_activeAnimation].getTexCoord(GSize(_texture.getWidth(), _texture.getHeight()), animationcoord);

            _shader->bind();

            glUniform2f(glGetUniformLocation(_shader->getProgram(), "animationCoord"), animationcoord.x, animationcoord.y);

            _mesh->draw();

            _shader->unbind();

            // Restore Matrix
            glPopMatrix();

            glDisable(GL_TEXTURE_2D);
        }

        /*
        Add animation to animations list
        from data given
        */
        void Sprite::addAnimation(std::string name, int nbFrame, GPos start, GSize size, float frequence) {
            Animation anim = Animation(nbFrame, start, size, frequence);
            _animations[name] = anim;
        }

        /*
        Reset animation frame
        Set once value
        Play animation asked if exists
        */
        void Sprite::playAnimation(std::string name, bool once) {
            /*
            If animation exists
            And different than active animation
            */
            if (_activeAnimation != name && _animations.find(name) != _animations.end()) {
                _animations[name].frame = 0;
                _animations[name].elapsedTime = 0.0f;
                _animations[name].once = once;
                _activeAnimation = name;
            }
        }


        void Sprite::setDrawSize(GSize s, bool cutTexture) {
            if(_mesh)
                delete _mesh;

            _drawSize = s;

            Gnin::Graphics::Vertex vertices[] = {
                    Gnin::Graphics::Vertex(-_drawSize.w / 2, -_drawSize.h / 2, 0, 0.0, 0.0),
                    Gnin::Graphics::Vertex(-_drawSize.w / 2, _drawSize.h / 2, 0, 0.0, (cutTexture ? (s.h / _texture.getHeight()) : 1.0f)),
                    Gnin::Graphics::Vertex(_drawSize.w / 2, -_drawSize.h / 2, 0, (cutTexture ? (s.w / _texture.getWidth()) : 1.0f), 0.0),
                    Gnin::Graphics::Vertex(_drawSize.w / 2, -_drawSize.h / 2, 0, (cutTexture ? (s.w / _texture.getWidth()) : 1.0f), 0.0),
                    Gnin::Graphics::Vertex(_drawSize.w / 2, _drawSize.h / 2, 0, (cutTexture ? (s.w / _texture.getWidth()) : 1.0f), (cutTexture ? (s.h / _texture.getHeight()) : 1.0f)),
                    Gnin::Graphics::Vertex(-_drawSize.w / 2, _drawSize.h / 2, 0, 0.0, (cutTexture ? (s.h / _texture.getHeight()) : 1.0f))
            };

            _mesh = new Gnin::Graphics::Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
        }
    }
}