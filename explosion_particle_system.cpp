#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "explosion_particle_system.h"

#include <iostream>

namespace game {

ExplosionParticleSystem::ExplosionParticleSystem(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture, GameObject *parent)
	: ParticleSystem(position, geom, shader, texture, parent){

    timeActive = 0.0f;
}


void ExplosionParticleSystem::Update(double delta_time) {
    timeActive += delta_time;

    if (timeActive >= 0.5f) { state_ = Died;  }

	// Call the parent's update method to move the object in standard way, if desired
	GameObject::Update(delta_time);
}


void ExplosionParticleSystem::Render(glm::mat4 view_matrix, double current_time){

    // Set up the shader
    shader_->Enable();

    // Set up the view matrix
    shader_->SetUniformMat4("view_matrix", view_matrix);

    // Setup the scaling matrix for the shader
    glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

    // Setup the rotation matrix for the shader
    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), angle_, glm::vec3(0.0, 0.0, 1.0));

    // Set up the translation matrix for the shader
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

    // Set up the parent transformation matrix
    glm::mat4 parent_rotation_matrix = glm::rotate(glm::mat4(1.0f), parent_->GetAngle(), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 parent_translation_matrix = glm::translate(glm::mat4(1.0f), parent_->GetPosition());
    glm::mat4 parent_transformation_matrix = parent_translation_matrix * parent_rotation_matrix;

    // Setup the transformation matrix for the shader
    glm::mat4 transformation_matrix = parent_transformation_matrix * translation_matrix * rotation_matrix * scaling_matrix;

    // Set the transformation matrix in the shader
    shader_->SetUniformMat4("transformation_matrix", transformation_matrix);

    // Set the time in the shader
    shader_->SetUniform1f("time", timeActive);

    // Set up the geometry
    geometry_->SetGeometry(shader_->GetShaderProgram());

    // Bind the particle texture
    glBindTexture(GL_TEXTURE_2D, texture_);

    // Draw the entity
    glDrawElements(GL_TRIANGLES, geometry_->GetSize(), GL_UNSIGNED_INT, 0);
}

} // namespace game
