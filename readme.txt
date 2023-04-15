Authors: Vitaly Dufour (101247178), William Graham (101228346)

OS: Windows

How to Play:
    You are a germ that has invaded the body, the body has many natural defenses
    and it will use them to repel you. Get the target score (15) in 2:30 minutes to win the game.
    You can acrue score by defeating enemies, stronger enemies will get you more score.


Controls:
W - move forwards
A - rotate left
D - rotate right
F - shoot a bullet in the forward direction
Space - Shoot several bullets in every direction, deals more damage than a normal bullet



Met Requirements: 

1. Game mechanics: Get 15 score in under 2 and a half minutes. Score can be obtained by defeating 
enemies, to get the score in the limited time you have to must make smart use of 
exploiting enemy AI, collecting powerups, and making good use of your special ammo.
TIP: Stronger enemies are worth more points

2. Enemies: There are 3 enemies with unique textures, weapons, and behaviour. Enemies give 1 health to the player
once killed.

All enemies have patrol behaviour, which makes them randomly move in a random direction
every few seconds. Enemies patrol when they are too far from the player

Red Bloodcells: Low health, when player is within range it will chase the player, once 
he gets close it will charge at the player with his anti-body coating, you have to get out of the way 
quick to avoid them (they stop, wait a second, and charge towards the position you were at when they
initially started the charge [so 1 second ago]). Gives 1 score.

White Bloodcells: Medium health, when player is near they will chase you down, once within
medium range they will shoot the player, while shooting will randomly dart around to make 
it hard for you to shoot them. If you get to close to him he will flee away until it is in comfortable
attack range. Gives 2 score.

Stem Cells: Large health, stationary and waits for the player to come to them, shoots
in all directions simultaneously at random intervals when player is close enough.
TIP: draw other enemies away from them and save them for last. Gives 2 score.

3. Weapons: player can shoot either a single bullet with the "F" key which has a cooldown. Or
can expand a special point (seen as 'SP: #' on the hud, which you pick up around the world) to shoot a special weapon
that fires in all directions, no cooldown but spamming this uses precious ammo. Cannot use this if you
have 0 special ammo. Both weapons use different sprites, and deal different amounts of damage.

4. Collectible Items: 3 collectibles, 1 uses a timer, all bring advantage to the player

Germ Surge: Player copies with half of the player's max health go on both sides of the player and fly mirror 
style next to the player and shoot when the player shoots for a limited time before dying (also uses
the player's special (space) alongside the player). They mimic the player's rotation and movement.
They will either die when they take enough damage (separately), or will both die 15 seconds after 
picking up this powerup. These copies can also pickup powerups for the player, 
and if they kill enemies, that will heal the player for 1.

Fat Coating: gives (2) ammo to special weapon (SP on the hud).

Bacteria Specks: Each one you get will upgrade your character,  growing the player and player bullets
slightly in size, reduces camera zoom, and get 3 extra max health, heals you for 3 as well.

5. Movement and Transformations: All movement is handled through transformations.
The game moves objects with both physically-based and parametric based equations. 
Some examples:

physically-based: Player(s), Bullets.
parametric bassed: All Enemies.

6. Collision detection: Collisions are detected in many ways, getting hit, picking up things, etc.

7. Game World: You can scroll, the map is made up of many different tiles with different appearences.
	       The world is fully randomized every time you run it, giving it a unique feel every time.

8. Particle Systems: There are 3 instances of particles, 2 are very different.

Enemy bullet hit/explosion: a blood red spark that scrapes off the player when an enemy bullet
hits him. Uses a medium amount of particles.

Player bullet trail: A thin germ trail of greenish-yellow ooze that follows player bullets, gets
larger the more powerful the bullet is (the more bacteria specks the player has picked up).
Uses a low amount of particles.

Player bullet hit/explosion: A yellowish-green color swap of the enemy bullet hit/explosion

9. UI: the player HUD scales with camera zoom and player movement. Displays in order from left to right:
current health, max health, a timer and ammo count for the special shot (SP).

10. Advanced method: Steering Behaviours, all enemies have the chase behaviour.
The white bloodcell also has the flee behaviour, implementations are discussed above in "2. Enemies"

11. Code readability and organization:
We left comments frequently, and where possible organized code into functions/methods.

12. Bonus: The player's copies from the germ surge powerup use a special shader to show a 'ghost-like'
	   effect, so it is easy for the player to know who he is among the 3 'players' on the screen.

Credits:
All art either provided by Professor Oliver or created by the group for this project.