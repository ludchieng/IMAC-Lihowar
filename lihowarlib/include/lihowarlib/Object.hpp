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

/**
 * @brief Represents a game object in a game scene
 */
class Object : public dp::Subject {

public:
    // SUB CLASS

    /**
     * @brief Represents a position, rotation and scale state for an game entity
     */
    class PRS {
    public:
        // CONSTANTS
        /**
         * @brief Unit vector X axis
         */
        static const glm::vec3 X;

        /**
         * @brief Unit vector Y axis
         */
        static const glm::vec3 Y;

        /**
         * @brief Unit vector Z axis
         */
        static const glm::vec3 Z;

        /**
         * @brief Unit vector X axis with a forth coordinate
         */
        static const glm::vec4 vec4_X;

        /**
         * @brief Unit vector Y axis with a forth coordinate
         */
        static const glm::vec4 vec4_Y;

        /**
         * @brief Unit vector Z axis with a forth coordinate
         */
        static const glm::vec4 vec4_Z;

    private:
        // MEMBERS
        /**
         * @brief position
         */
        glm::vec3 _pos = glm::vec3(0.f);
        /**
         * @brief rotation in degrees
         */
        glm::vec3 _rot = glm::vec3(0.f); // degrees
        /**
         * @brief scale
         */
        glm::vec3 _sca = glm::vec3(1.f);

    public:
        // CONTRUCTORS & DESTRUCTORS

        /**
         * @brief PRS class constructor
         */
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
    /**
     * @brief Reference to a mesh instance
     */
    Mesh &_mesh;

    /**
     * @brief Pointer to a Material
     */
    std::shared_ptr<Material> _material;

    /**
     * @brief Position, rotation and scale state
     */
    PRS _prs;

    /**
     * @brief List of sub-objects
     *
     * The PRS of the children (sub-objects) are affected by their parent PRS.
     * When an Object instance is moving through space, its children will do so.
     */
    std::list< std::unique_ptr<Object> > _subobjects;

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Object class constructor
     * @param mesh
     * @param diffuseTexId  Diffuse texture GL ID
     * @param prs           Position, rotation and scale state
     */
    explicit Object(
            Mesh& mesh,
            GLuint diffuseTexId = 0,
            PRS prs = PRS())
        :_mesh(mesh),
         _material(new Material(diffuseTexId)),
         _prs(std::move(prs))
    {}

    /**
     * @brief Object class constructor
     * @param mesh
     * @param material
     * @param prs       Position, rotation and scale state
     */
    explicit Object(
            Mesh& mesh,
            Material &material,
            PRS prs = PRS())
        :_mesh(mesh),
         _material(&material),
         _prs(std::move(prs))
    {}

    /**
     * @brief Object class destructor
     */
    virtual ~Object() = default;
    
public:
    // INTERFACE

    /**
     * @brief Gets the position, rotation and scale state
     * @return Returns the position, rotation and scale state
     */
    PRS &prs() { return _prs; }
    PRS prs() const { return _prs; }


    /**
     * @brief Gets the material
     * @return Returns the material
     */
    Material &material() { return *_material; }
    Material material() const { return *_material; }

    /**
     * Gets the sub-objects list
     * @return Returns the sub-objects list
     */
    std::list< std::unique_ptr<Object> > &subobjects() { return _subobjects; }
    const std::list< std::unique_ptr<Object> > &subobjects() const { return _subobjects; }


    /**
     * @brief Asserts that the object is an instance of a given sub-class
     * @tparam T  Sub-class to try to cast to
     * @return Returns true if the object is of the specified sub-class, false otherwise
     */
    template <typename T>
    bool isInstanceOf() const { return nullptr != dynamic_cast<const T*>(this); }


    /**
     * @brief Adds a sub-object
     * @param object  Object to add as sub-object
     */
    virtual void add(std::unique_ptr<Object> object);
    virtual void add(Object *object) { add(std::unique_ptr<Object>(object)); }


    /**
     * @brief Updates state of the Object
     */
    virtual void update();

    /**
     * @brief Draws the object
     */
    void render() const;


    /**
     * @brief Translate the object
     * @param dpos  Delta position vector
     */
    void translate(const glm::vec3 &dpos) { _prs.pos() += dpos; }

    /**
     * @brief Rotate the object
     * @param drot  Delta rotation vector
     */
    void rotate(const glm::vec3 &drot) { _prs.rot() += drot; }

    /**
     * @brief Scale the object
     * @param dsca  Delta scale vector
     */
    void scale(const glm::vec3 &dsca) { _prs.sca() += dsca; }

    /**
     * @brief Gets the Model matrix
     * @return Returns the Model matrix
     */
    glm::mat4 matModel() const;


    /**
     * @brief Traverses recursively its sub-objects to find all the
     * instances of a given Object sub-class
     * @tparam T  Sub-class we are looking for
     * @return  Returns a list of sub-objects that matches the
     * requested sub-class
     */
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
