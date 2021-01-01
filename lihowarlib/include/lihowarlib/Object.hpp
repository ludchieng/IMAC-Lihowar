/*
 *  Copyright (c) 2020-2021 Lihowar
 *
 *  This software is licensed under OSEF License.
 *
 *  The "Software" is defined as the pieces of code, the documentation files, the config
 *  files, the textures assets, the Wavefront OBJ assets, the screenshot image, the sound
 *  effects and music associated with.
 *
 *  This Software is licensed under OSEF License which means IN ACCORDANCE WITH THE LICENSE
 *  OF THE DEPENDENCIES OF THE SOFTWARE, you can use it as you want for any purpose, but
 *  it comes with no guarantee of any kind, provided that you respects the license of the
 *  software dependencies of the piece of code you want to reuse. The dependencies are
 *  listed at the end of the README given in the directory root of the Lihowar repository.
 */
#pragma once
#ifndef LIHOWAR_OBJECT_HPP
#define LIHOWAR_OBJECT_HPP

#include <list>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/AssetManager.hpp>
#include <lihowarlib/Mesh.hpp>
#include <lihowarlib/Texture.hpp>
#include <lihowarlib/Material.hpp>
#include <lihowarlib/designpattern/Subject.hpp>
#include <lihowarlib/designpattern/Observer.hpp>
#include <lihowarlib/programs/Program.hpp>
#include <lihowarlib/programs/MultiLightsProgram.hpp>

namespace lihowar {

class Object : public dp::Subject {

public:
    // SUB CLASS
    class PRS {
    public:
        // CONSTANTS
        static const glm::vec3 X;
        static const glm::vec3 Y;
        static const glm::vec3 Z;
        static const glm::vec4 vec4_X;
        static const glm::vec4 vec4_Y;
        static const glm::vec4 vec4_Z;

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
        glm::vec3 rotRadians() const { return glm::radians(_rot); }
        glm::vec3 sca() const { return _sca; }

    };

protected:
    // MEMBERS
    Mesh &_mesh;
    std::shared_ptr<Material> _material;
    PRS _prs;
    std::list< std::unique_ptr<Object> > _subobjects;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Object(
            Mesh& mesh,
            GLuint diffuseTexId = 0,
            PRS prs = PRS())
        :_mesh(mesh),
         _material(new Material(diffuseTexId)),
         _prs(std::move(prs))
    {}

    explicit Object(
            Mesh& mesh,
            Material &material,
            PRS prs = PRS())
        :_mesh(mesh),
         _material(&material),
         _prs(std::move(prs))
    {}

    // TODO
    //Object(const Object& g);

    virtual ~Object() = default;
    
public:
    // INTERFACE
    PRS &prs() { return _prs; }
    PRS prs() const { return _prs; }
    Material &material() { return *_material; }
    Material material() const { return *_material; }

    std::list< std::unique_ptr<Object> > &subobjects() { return _subobjects; }
    const std::list< std::unique_ptr<Object> > &subobjects() const { return _subobjects; }

    template <typename T>
    bool isInstanceOf() const { return nullptr != dynamic_cast<const T*>(this); }

    virtual void add(std::unique_ptr<Object> object);
    virtual void add(Object *object) { add(std::unique_ptr<Object>(object)); }

    virtual void update();
    void render() const;

    void translate(const glm::vec3 &dpos) { _prs.pos() += dpos; }
    void rotate(const glm::vec3 &drot) { _prs.rot() += drot; }
    void scale(const glm::vec3 &dsca) { _prs.sca() += dsca; }
    glm::mat4 matModel() const;


    template <typename T>
    std::list<std::shared_ptr<T>> &findAll() {
        auto res = new std::list<std::shared_ptr<T>>();
        if (isInstanceOf<T>())
            res->push_back(std::shared_ptr<T>(dynamic_cast<T*>(this)));

        auto it = _subobjects.begin();
        while (it != _subobjects.end()) {
            res->splice(res->end(), (**it).findAll<T>());
            ++it;
        }
        return *res;
    }

};

}


#endif //LIHOWAR_OBJECT_HPP
