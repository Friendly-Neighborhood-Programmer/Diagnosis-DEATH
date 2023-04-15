#include "player_game_object.h"
#include <iostream>
#include "player_bullet_game_object.h"
#include <glm/gtc/matrix_transform.hpp>
namespace game {

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture)
	: GameObject(position, geom, shader, texture) {
    oType = Player;
    maxVelocity_ = 5;
    spiralShotAmt = 10;
    damageTimer = 0;
}

// Update function for moving the player object around
void PlayerGameObject::Update(double delta_time) {
    time += delta_time;
    // TODO MAKE FEEL BETTER, TWEEK VALUES
    if (glm::length(velocity_) > 2.0f) {
        velocity_ -= velocity_ * 1.75f * glm::vec3(delta_time);
    } else if (glm::length(velocity_) < 0.5f && !accelerating) {
        velocity_ = glm::vec3(0.0f, 0.0f, 0.0f);
    } else if ((glm::length(velocity_) < 2.0f)) {
        velocity_ -= velocity_ * 0.9f * glm::vec3(delta_time);
    }

	// Call the parent's update method to move the object in standard way, if desired
	GameObject::Update(delta_time);
}

BulletGameObject* PlayerGameObject::shoot(Geometry* sprite, Shader* shader, GLuint texture) {
    BulletGameObject* bullet = new PlayerBulletGameObject(position_, angle_, GetBearing(), sprite, shader, texture);
    bullet->setDamage(getDamage());
    return bullet;
}

int PlayerGameObject::dealDamage() {
    if (damageTimer <= time) {
        damageTimer = time + 0.75;
        return damage;
    }
    return 0;
}

vector<PlayerBulletGameObject*> PlayerGameObject::spiralShoot(Geometry* sprite, Shader* shader, GLuint texture, int numScales) {
    bulletAmount--;
    vector<PlayerBulletGameObject*> bullets;

    for (int i = 0; i < spiralShotAmt; i++) {
        float angle = angle_ + glm::radians(360.f / spiralShotAmt * i);
        glm::vec3 dir = glm::vec3(glm::cos(angle), glm::sin(angle), 0);

        PlayerBulletGameObject* bullet = new PlayerBulletGameObject(position_, angle-glm::radians(90.f), dir, sprite, shader, texture);
        bullet->setDamage(2);
        bullet->SetScale(2 + ((numScales * 0.5)));
        
        //add to collection of all bullets
        bullets.push_back(bullet);
    }

    return bullets;
}

void PlayerGameObject::Render(glm::mat4 view_matrix, double current_time) {
    if (state_ == DyingBullet) return; //if dying bullet, dont render
    // Set up the shader
    shader_->Enable();

    // Set up the view matrix
    shader_->SetUniformMat4("view_matrix", view_matrix);

    // store all transformationsw
    glm::mat4 transformation_matrix;

    // integrate hierarchical transformation from parent's transformation matrix
    /*if (parent) {
        glm::mat4 p_scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(parent->scale_, parent->scale_, 1.0));
        glm::mat4 p_rotation_matrix = glm::rotate(glm::mat4(1.0f), parent->angle_, glm::vec3(0.0, 0.0, 1.0));
        glm::mat4 p_translation_matrix = glm::translate(glm::mat4(1.0f), parent->position_);

        transformation_matrix = p_translation_matrix * p_rotation_matrix * p_scaling_matrix;
    }*/

    // this object's transformations
    // Setup the scaling matrix for the shader
    glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

    // Setup the rotation matrix for the shader
    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), angle_, glm::vec3(0.0, 0.0, 1.0));

    // Set up the translation matrix for the shader
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

    // Setup the transformation matrix for the shader
    transformation_matrix *= translation_matrix * rotation_matrix * scaling_matrix;

    // Set the transformation matrix in the shader
    shader_->SetUniformMat4("transformation_matrix", transformation_matrix);

    shader_->SetUniform1f("time", current_time);

    shader_->SetUniform1i("special", 1);

    // Set up the geometry
    geometry_->SetGeometry(shader_->GetShaderProgram());

    // Bind the entity's texture
    glBindTexture(GL_TEXTURE_2D, texture_);

    // Draw the entity
    glDrawElements(GL_TRIANGLES, geometry_->GetSize(), GL_UNSIGNED_INT, 0);
}
} // namespace game
