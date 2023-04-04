#ifndef COLLECTIBLE_OBJECT_H
#define COLLECTIBLE_OBJECT_H

#include "game_object.h"

namespace game {

    class CollectibleGameObject : public GameObject {

    public:
        CollectibleGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

        // Update function for moving the player object around
        void Update(double delta_time) override;
    private:
    };


} // namespace game

#endif // COLLECTIBLE_OBJECT_H#pragma once
