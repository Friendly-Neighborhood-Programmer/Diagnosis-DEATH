#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "game_object.h"
#include "bullet_game_object.h"
namespace game {

GameObject::GameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture) 
{
    // Initialize all attributes
    position_ = startPos = position;
    scale_ = 1.0;
    angle_ = 0.0;
    velocity_ = glm::vec3(0.0f, 0.0f, 0.0f); // Starts out stationary
    geometry_ = geom;
    shader_ = shader;
    texture_ = texture;
    state_ = Active;
    shotCooldown = 0.0f;
    timeAlive = 0.0f;
    parent = nullptr;
    maxVelocity_ = 6;
    accelerating = false;
    damage = 1;
    particle = nullptr;
    bullet = nullptr;
    bulletAmount = 3;
    cooldown = 0.7f;
}


glm::vec3 GameObject::GetBearing(void) {

    // Assumes sprite is initially rotated by 90 degrees
    float pi_over_two = glm::pi<float>() / 2.0f;
    glm::vec3 dir(cos(angle_ + pi_over_two), sin(angle_ + pi_over_two), 0.0);
    return dir;
}


glm::vec3 GameObject::GetRight(void) {

    // Assumes sprite is initially rotated by 90 degrees
    glm::vec3 dir(cos(angle_), sin(angle_), 0.0);
    return dir;
}


void GameObject::SetAngle(float angle){ 

    // Set angle of the game object
    // Make sure angle is in the range [0, 2*pi]
    float two_pi = 2.0f*glm::pi<float>();
    angle = fmod(angle, two_pi);
    if (angle < 0.0){
        angle += two_pi;
    }
    angle_ = angle;
}

void GameObject::SetParent(GameObject *p) {
    parent = p;
}

bool GameObject::canShoot() {
    if (shotCooldown >= cooldown) {
        shotCooldown = 0.0f;
        return true;
    }
    return false;
}

BulletGameObject* GameObject::shoot(Geometry* sprite, Shader* shader, GLuint texture) {
    BulletGameObject* bullet = new BulletGameObject(position_, sprite, shader, texture);
    return bullet;
}
void GameObject::die() {
    state_ = Died;
    if (particle != nullptr) {
        particle->die();
    }
}

bool GameObject::isColliding(GameObject *other) {
    // ray from the object's creation point to where it is currently
    glm::vec3 ray = position_ - startPos;

    glm::vec3 circlePos = other->GetPosition();

    // dot product from the circle to the ray
    float dot = (((circlePos.x - startPos.x) * (position_.x - startPos.x)) + ((circlePos.y - startPos.y) * (position_.y - startPos.y))) / pow(glm::length(ray), 2);

    // find the closest point to the circle on the ray
    glm::vec3 point = startPos + dot * ray;

    //  the circle is actually on the ray
    float margin = 0.1f;
    float circleToThis = glm::length(circlePos - position_);
    float circleToStart = glm::length(circlePos - startPos);

    bool onLine = circleToThis + circleToStart >= glm::length(ray) - margin && circleToThis + circleToStart <= glm::length(ray) + margin;
    if (!onLine) return false;

    // a collision has occured
    if (glm::length(point - circlePos) <= 0.4f) { return true; }

    return false;
}


void GameObject::Update(double delta_time) {
    shotCooldown += delta_time;
    timeAlive += delta_time;

    // Update object position with Euler integration
    position_ += velocity_ * ((float) delta_time);

    if (oType == Blade) { angle_ += 0.02; }

    if (parent && parent->state_ == Exploded) { state_ = Died; }

    // Check if object exploded
    if (state_ == Exploded) {
        velocity_ = glm::vec3(0.0f);

        // Increase explosion timer
        exp_time_ += delta_time;
        // Check if we reached the end of the explosion
        if (exp_time_ >= exp_end_time_) {
            // The object died now
            state_ = Died;
        }
    }
}


void GameObject::Render(glm::mat4 view_matrix, double current_time){
    if (state_ == DyingBullet) return; //if dying bullet, dont render
    // Set up the shader
    shader_->Enable();

    // Set up the view matrix
    shader_->SetUniformMat4("view_matrix", view_matrix);

    // store all transformationsw
    glm::mat4 transformation_matrix;

    // integrate hierarchical transformation from parent's transformation matrix
    if (parent) {
        glm::mat4 p_scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(parent->scale_, parent->scale_, 1.0));
        glm::mat4 p_rotation_matrix = glm::rotate(glm::mat4(1.0f), parent->angle_, glm::vec3(0.0, 0.0, 1.0));
        glm::mat4 p_translation_matrix = glm::translate(glm::mat4(1.0f), parent->position_);

        transformation_matrix = p_translation_matrix * p_rotation_matrix * p_scaling_matrix;
    }

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

    // Set up the geometry
    geometry_->SetGeometry(shader_->GetShaderProgram());

    // Bind the entity's texture
    glBindTexture(GL_TEXTURE_2D, texture_);

    // Draw the entity
    glDrawElements(GL_TRIANGLES, geometry_->GetSize(), GL_UNSIGNED_INT, 0);
}

void GameObject::Explode(GLuint exp_texture) {

    // Set the state of the object as exploded
    state_ = Exploded;
    // Start explosion timer
    exp_time_ = 0.0;
    // Explosion should end after 3 seconds
    exp_end_time_ = 3.0;
    // Update the texture of the game object
    texture_ = exp_texture;
}
void GameObject::SetVelocity(const glm::vec3& velocity) {
    if (maxVelocity_ > glm::length(velocity))
        velocity_ = velocity;
    else velocity_ = glm::vec3(maxVelocity_) * glm::normalize(velocity);
}
void GameObject::setAccelerating(bool acc) {
    accelerating = acc;
}

void GameObject::takeDamage(int dmg) {
    curHealth -= dmg;
    if (curHealth <= 0) {
        die();
    }
}

void GameObject::heal(int amount) {
    curHealth += amount;
    if (curHealth > maxHealth) {
        curHealth = maxHealth;
    }
}

} // namespace game
