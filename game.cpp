#include <stdexcept>
#include <string>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp> 
#include <SOIL/SOIL.h>
#include <iostream>

#include <path_config.h>

#include "sprite.h"
#include "particles.h"
#include "trail_particles.h"
#include "explosion_particles.h"
#include "shader.h"
#include "player_game_object.h"
#include "enemy_game_object.h"
#include "bullet_game_object.h"
#include "particle_system.h"
#include "explosion_particle_system.h"
#include "game.h"

using namespace std;

namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Globals that define the OpenGL window and viewport
const char *window_title_g = "Final Project";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const glm::vec3 viewport_background_color_g(0.0, 0.0, 1.0);

// Directory with game resources such as textures
const std::string resources_directory_g = RESOURCES_DIRECTORY;


Game::Game(void)
{
    // Don't do work in the constructor, leave it for the Init() function
}


void Game::Init(void)
{

    // Initialize the window management library (GLFW)
    if (!glfwInit()) {
        throw(std::runtime_error(std::string("Could not initialize the GLFW library")));
    }

    // Set window to not resizable
    // Required or else the calculation to get cursor pos to screenspace will be incorrect
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 

    // Create a window and its OpenGL context
    window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g, NULL, NULL);
    if (!window_) {
        glfwTerminate();
        throw(std::runtime_error(std::string("Could not create window")));
    }

    // Make the window's OpenGL context the current one
    glfwMakeContextCurrent(window_);

    // Initialize the GLEW library to access OpenGL extensions
    // Need to do it after initializing an OpenGL context
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        throw(std::runtime_error(std::string("Could not initialize the GLEW library: ") + std::string((const char *)glewGetErrorString(err))));
    }

    // Set event callbacks
    glfwSetFramebufferSizeCallback(window_, ResizeCallback);

    // Initialize sprite geometry
    sprite_ = new Sprite();
    sprite_->CreateGeometry();

    // Initialize particle geometry
    particles_ = new Particles();
    particles_->CreateGeometry();

    // Initialize particle geometry
    explosion_particles_ = new ExplosionParticles();
    explosion_particles_->CreateGeometry();

    // Initialize particle geometry
    trail_particles_ = new TrailParticles();
    trail_particles_->CreateGeometry();

    // Initialize particle shader
    particle_shader_.Init((resources_directory_g+std::string("/particle_vertex_shader.glsl")).c_str(), (resources_directory_g+std::string("/particle_fragment_shader.glsl")).c_str());
    trail_particle_shader_.Init((resources_directory_g+std::string("/trail_particle_vertex_shader.glsl")).c_str(), (resources_directory_g+std::string("/trail_particle_fragment_shader.glsl")).c_str());
    explosion_particle_shader_.Init((resources_directory_g+std::string("/explosion_particle_vertex_shader.glsl")).c_str(), (resources_directory_g+std::string("/explosion_particle_fragment_shader.glsl")).c_str());

    // Initialize sprite shader
    sprite_shader_.Init((resources_directory_g+std::string("/sprite_vertex_shader.glsl")).c_str(), (resources_directory_g+std::string("/sprite_fragment_shader.glsl")).c_str());

    // Initialize time
    current_time_ = 0.0;
}


Game::~Game()
{
    // Free memory for all objects
    // Only need to delete objects that are not automatically freed
    delete sprite_;
    delete particles_;
    for (int i = 0; i < game_objects_.size(); i++){
        delete game_objects_[i];
    }

    // Close window
    glfwDestroyWindow(window_);
    glfwTerminate();
}


void Game::Setup(void)
{
    // Setup the game world

    // Load textures
    SetAllTextures();

    // Setup the player object (position, texture, vertex count)
    // Note that, in this specific implementation, the player object should always be the first object in the game object vector 
    game_objects_.push_back(new PlayerGameObject(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, tex_[0]));
    game_objects_.push_back(new GameObject(glm::vec3(0.0f, 0.0f, -0.1f), sprite_, &sprite_shader_, tex_[7]));
    game_objects_[1]->SetParent(game_objects_[0]);
    game_objects_[1]->setType(GameObject::Blade);

    // Setup other objects
    int num_enemies = 10;
    for (int i = 0; i < num_enemies; i++) {
        game_objects_.push_back(new EnemyGameObject(glm::vec3(randF(-3.0, 3.0), randF(-3.0, 3.0), 0.0f), sprite_, &sprite_shader_, tex_[2]));
    }

    // Setup background
    // In this specific implementation, the background is always the
    // last object
    GameObject *background = new GameObject(glm::vec3(0.0f, 0.0f, 2.0f), sprite_, &sprite_shader_, tex_[3]);
    background->SetScale(10.0);
    game_objects_.push_back(background);

    // Setup particle system
    GameObject *particles = new ParticleSystem(glm::vec3(0.0f, -0.5f, 0.0f), particles_, &particle_shader_, tex_[4], game_objects_[0]);
    particles->SetScale(0.2);
    game_objects_.push_back(particles);
}


void Game::ResizeCallback(GLFWwindow* window, int width, int height)
{

    // Set OpenGL viewport based on framebuffer width and height
    glViewport(0, 0, width, height);
}


void Game::SetTexture(GLuint w, const char *fname)
{
    // Bind texture buffer
    glBindTexture(GL_TEXTURE_2D, w);

    // Load texture from a file to the buffer
    int width, height;
    unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    // Texture Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Texture Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Game::SetAllTextures(void)
{
    // Load all textures that we will need
    glGenTextures(NUM_TEXTURES, tex_);
    SetTexture(tex_[0], (resources_directory_g+std::string("/textures/destroyer_red.png")).c_str());
    SetTexture(tex_[1], (resources_directory_g+std::string("/textures/destroyer_green.png")).c_str());
    SetTexture(tex_[2], (resources_directory_g+std::string("/textures/destroyer_blue.png")).c_str());
    SetTexture(tex_[3], (resources_directory_g+std::string("/textures/stars.png")).c_str());
    SetTexture(tex_[4], (resources_directory_g+std::string("/textures/orb.png")).c_str());
    SetTexture(tex_[5], (resources_directory_g + std::string("/textures/explosion.png")).c_str());
    SetTexture(tex_[6], (resources_directory_g + std::string("/textures/bullet.png")).c_str());
    SetTexture(tex_[7], (resources_directory_g + std::string("/textures/blade.png")).c_str());
    glBindTexture(GL_TEXTURE_2D, tex_[0]);
}


void Game::MainLoop(void)
{
    // Loop while the user did not close the window
    double last_time = glfwGetTime();
    while (!glfwWindowShouldClose(window_)){

        // Clear background
        glClearColor(viewport_background_color_g.r,
                     viewport_background_color_g.g,
                     viewport_background_color_g.b, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set view to zoom out, centered by default at 0,0
        float camera_zoom = 0.25f;
        glm::mat4 view_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(camera_zoom, camera_zoom, camera_zoom));

        // Calculate delta time
        double current_time = glfwGetTime();
        double delta_time = current_time - last_time;
        last_time = current_time;

        // Update other events like input handling
        glfwPollEvents();

        // Update the game
        Update(view_matrix, delta_time);

        // Push buffer drawn in the background onto the display
        glfwSwapBuffers(window_);
    }
}


void Game::Update(glm::mat4 view_matrix, double delta_time)
{

    // Update time
    current_time_ += delta_time;

    // Handle user input
    Controls(delta_time);

    // Update and render all game objects
    for (int i = 0; i < game_objects_.size(); i++) {
        // Get the current game object
        GameObject* current_game_object = game_objects_[i];

        // Update the current game object
        current_game_object->Update(delta_time);

        // Check if game object already died
        if (current_game_object->GetState() == GameObject::Died) {
            // Remove object from the list of objects
            game_objects_.erase(game_objects_.begin() + i);
            // Delete game object from memory
            delete current_game_object;
            // You could also keep the object and respawn it later...
            // Make sure we don't skip an element when we advance the loop
            i--;
            continue;
        }

        // timeout for bullets, kill after 1 second of hitting nothing
        if (current_game_object->getType() == GameObject::Bullet &&
            current_game_object->timeAlive >= 1.0f && 
            current_game_object->GetState() == GameObject::Active) {

            current_game_object->Explode(tex_[5]);
            GameObject* particles = new ExplosionParticleSystem(glm::vec3(0.0f, 0.0f, -0.5f), explosion_particles_, &explosion_particle_shader_, tex_[4], current_game_object);
            particles->SetScale(0.08);
            game_objects_.push_back(particles);
            continue;
        }


        // Check for collision with other game objects
        // Note the loop bounds: we avoid testing the last object since
        // it's the background covering the whole game world
        for (int j = i + 1; j < (game_objects_.size()-1); j++) {
            GameObject* other_game_object = game_objects_[j];

            if (current_game_object->GetState() == GameObject::Exploded || other_game_object->GetState() == GameObject::Exploded) continue;
            if (current_game_object->getType() == GameObject::Particles || other_game_object->getType() == GameObject::Particles) continue;

            // Compute distance between object i and object j
            float distance = glm::length(current_game_object->GetPosition() - other_game_object->GetPosition());
            // If distance is below a threshold, we have a collision
            //if (distance < 0.8f) {

            //    if (current_game_object->getType() == GameObject::Player && other_game_object->getType() == GameObject::Bullet) {
            //        continue;
            //    }
            //    
            //    // check if bullet and enemy is colliding
            //}

            // check for raycast collisions between bullets and enemies
            if (current_game_object->getType() == GameObject::Enemy && other_game_object->getType() == GameObject::Bullet) {
                if (!other_game_object->isColliding(current_game_object)) { continue; }

                current_game_object->Explode(tex_[5]);
                current_game_object->SetScale(1.5f);
                GameObject* explosion1 = new ExplosionParticleSystem(glm::vec3(0.0f, 0.0f, -0.5f), explosion_particles_, &explosion_particle_shader_, tex_[4], current_game_object);
                explosion1->SetScale(0.08);
                game_objects_.push_back(explosion1);

                other_game_object->Explode(tex_[5]);
                GameObject* explosion2 = new ExplosionParticleSystem(glm::vec3(0.0f, 0.0f, -0.5f), explosion_particles_, &explosion_particle_shader_, tex_[4], other_game_object);
                explosion2->SetScale(0.08);
                game_objects_.push_back(explosion2);
            }
        }

        // Render game object
        current_game_object->Render(view_matrix, current_time_);
    }
}


void Game::Controls(double delta_time)
{
    // Get player game object
    PlayerGameObject *player = dynamic_cast<PlayerGameObject*>(game_objects_[0]);
    // Get current position and angle and velocity
    glm::vec3 curpos = player->GetPosition();
    float angle = player->GetAngle();
    glm::vec3 vel = player->GetVelocity();
    // Compute current bearing direction
    glm::vec3 dir = player->GetBearing();
    // Adjust motion increment and angle increment 
    // if translation or rotation is too slow
    float speed = delta_time*500.0;
    float motion_increment = 0.001*speed;
    float angle_increment = (glm::pi<float>() / 1800.0f)*speed * 200;

    // Check for player input and make changes accordingly
    if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
        player->setAccelerating(true);
        player->SetVelocity(vel + dir * 0.02f * speed);
    }
    else {
        player->setAccelerating(false);
    }
    if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
        player->SetVelocity(vel - vel * 0.005f * speed);
    }
    if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
        player->SetAngle(angle - glm::radians(angle_increment));
    }
    if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
        player->SetAngle(angle + glm::radians(angle_increment));
    }
    if (glfwGetKey(window_, GLFW_KEY_F) == GLFW_PRESS) {
        if (player->shoot()) {
            GameObject* bullet = new BulletGameObject(curpos, sprite_, &sprite_shader_, tex_[6]);
            bullet->SetScale(0.8);
            bullet->SetAngle(angle);
            bullet->SetVelocity(player->GetBearing() * 5.0f);
            game_objects_.push_back(bullet);

            GameObject* particles = new ParticleSystem(glm::vec3(0.0f, -0.4f, -0.5f), trail_particles_, &trail_particle_shader_, tex_[4], bullet);
            particles->SetScale(0.08);
            game_objects_.push_back(particles);
        }
    }
    if (glfwGetKey(window_, GLFW_KEY_Z) == GLFW_PRESS) {
        player->SetPosition(curpos - motion_increment*player->GetRight());
    }
    if (glfwGetKey(window_, GLFW_KEY_C) == GLFW_PRESS) {
        player->SetPosition(curpos + motion_increment*player->GetRight());
    }
    if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_, true);
    }
}

float Game::randF(float min, float max) {
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}
       
} // namespace game
