#ifndef LIHOWAR_GAMEOBJECT_HPP
#define LIHOWAR_GAMEOBJECT_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/Model.hpp>
#include <utility>

namespace lihowar {

class GameObject {

public:
    // SUB CLASS
    class PRS {
    private:
        // MEMBERS
        glm::vec3 _pos = glm::vec3(0.f);
        glm::vec3 _rot = glm::vec3(0.f); // degrees
        glm::vec3 _sca = glm::vec3(1.f);

    public:
        // CONTRUCTORS & DESTRUCTORS
        explicit PRS(const glm::vec3& position = glm::vec3(0.f),
                     const glm::vec3& rotation = glm::vec3(0.f),
                     const glm::vec3& scale    = glm::vec3(1.f) )
                : _pos(position), _rot(rotation), _sca(scale)
        {}

    public:
        // INTERFACE
        glm::vec3 &pos() { return _pos; }
        glm::vec3 &rot() { return _rot; }
        glm::vec3 &sca() { return _sca; }
        glm::vec3 pos() const { return _pos; }
        glm::vec3 rot() const { return _rot; }
        glm::vec3 sca() const { return _sca; }

    };

private:
    // MEMBERS
    Model &_model;
    PRS _prs;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit GameObject(Model& model, PRS prs = PRS())
       :_model(model), _prs(prs)
    {}

    // TODO
    //GameObject(const GameObject& g);

    ~GameObject() = default;
    
public:
    // INTERFACE
    PRS &prs() { return _prs; }
    void translate(const glm::vec3 &dpos) { _prs.pos() += dpos; }
    glm::mat4 matModel() const;
    void render();
};

}


#endif //LIHOWAR_GAMEOBJECT_HPP
