#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "shader.h"
#include "game_object.h"
#include "player_game_object.h"
#include "text_game_object.h"

#define NUM_PLAYERS 3

namespace game {

    // A class for holding the main game objects
    class Game {

        public:
            // Constructor and destructor
            Game(void);
            ~Game();

            // Call Init() before calling any other method
            // Initialize graphics libraries and main window
            void Init(void); 

            // Set up the game (scene, game objects, etc.)
            void Setup(void);

            // Run the game (keep the game active)
            void MainLoop(void); 

            void addGameObject(GameObject*);

        private:
            // Main window: pointer to the GLFW window structure
            GLFWwindow *window_;
            float camera_zoom;
            // Sprite geometry
            Geometry *sprite_;

            // Particle geometry for exhaust, bullet and explosion
            Geometry *particles_;
            Geometry *trail_particles_;
            Geometry *explosion_particles_;

            // Shader for rendering sprites in the scene
            Shader sprite_shader_;

            // Shader for rendering particles
            Shader particle_shader_;
            Shader trail_particle_shader_;
            Shader explosion_particle_shader_;

            // Shader for rendering text
            Shader text_shader_;

            float germTimer;
            bool germActivated;

            int numScales;

            // References to textures
#define NUM_TEXTURES 13
            GLuint tex_[NUM_TEXTURES];

            // List of game objects
            std::vector<GameObject*> game_objects_;

            // Keep track of time
            double current_time_;

            // Callback for when the window is resized
            static void ResizeCallback(GLFWwindow* window, int width, int height);

            // Set a specific texture
            void SetTexture(GLuint w, const char *fname);

            // Load all textures
            void SetAllTextures();

            // Handle user input
            void Controls(double delta_time);

            // Update the game based on user input and simulation
            void Update(glm::mat4 view_matrix, double delta_time);

            float Game::randF(float min, float max);

            //new stuff
            PlayerGameObject* players[NUM_PLAYERS];

            //UI stuff
            void adjustUiElts();
            void setTimer(double time);
            std::vector<TextGameObject*> UI_objects_;
            TextGameObject* healthText;
            TextGameObject* timerText;
            TextGameObject* SSText;

    }; // class Game

} // namespace game

#endif // GAME_H_
