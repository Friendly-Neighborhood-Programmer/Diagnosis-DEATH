OS: Windows

- added weapon that fires a bullet object when F key is pressed.
- there is a 1.5 second cooldown to shooting implemented in GameObject class.

- bullets explode automatically if they do not hit anything after 1 second.

- 10 enemies are placed randomly on startup.

- Uses ray circle collision to detect hits between bullets and enemies.
- both objects explode and show sprite with particles.

- particle trail and explosion particles for bullets are implemented with their 
  own shader files and vertex/fragment shader files.
  
- hierarchical transformation of blade with a pointer to the player as it's parent.

Credits:
Provided sprites used