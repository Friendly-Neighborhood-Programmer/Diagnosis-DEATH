OS: Windows

How to Play:
    You are a germ that has invaded the body, the body has many natural defences
    and it will use them to repel you. Get the target score in 2 minutes to win the game.
    You can acrue score by defeting enemys, stronger enemys will get you more score.


Controls:
W-move forword
A - rotate left
D - rotate right
F - Shoot a bullet in the forword direction
Space - Shoot several bullets in every direction



Met Requirments: 

1. Game mechanics: Get the target score in under 2 minutes. Score is gotten by defeting 
enemys, to get the score in the limited time you have, you must make smart use of 
exploting enemy AI, collecting powerups, and making good use of your special ammo.

2. Enemies: There are 3 enemies with unique textures, weapons, and behavoir.

All Enemys: have patrol behavoir

Red Bloodcells: Low health, when player is within range will move towards player, once 
he gets close will charge at you with his anti-body coating, you have to get out of the way 
quick to avoid them.  

White Bloodcells: Medium health, when player is neer with chase you down, once within
range they shoot you at fixed intervols, while shooting will randomly dart around to make 
it hard for you to shoot them. If you get to close to him he will flee. 

Stem Cells: Large health, mostly stationary and waits for the player to come to them, shoots
in all directions simultaneously at random intervols. TIP: draw other enemys away from him
and save him for last.

3. Weapons: player can shoot either a single bullet with the "F" key which has a cooldown. Or
can expend a special point (which you pick up around the world) to shoot a special weapon
that fires in all directions, no cooldown but spamming this wastes precious ammo.

4. Collectible Items: 3 collectibles, 1 uses a timer, all bring advantage to the player

Germ Surge: Identical Color swapped copies of the player swoop in from all sides and fly mirror 
style next to the player and shoot when the player shoots for a limited time before dying, 
and can die prematurely from enemy fire.

Fat Coating: gives ammo to special weapon.

Bacteria specks: Each one you get will upgrade your character,  grow slightly in size, reduce 
camera zoom, and get extra health.

5. Movement and Transformations: All movment is handled through transformations.
The game moves objects with both physically-bassed and parametric bassed equations. 
Some exampls.

physically-bassed: Player(s), Bullets.
parametric bassed: All Enemys.

6. Collision detection: Collisions are detected in many ways, getting hit, picking up things, etc.

7. Game World: You can scroll, the map is made up of many diffrent tiles with diffrent apearences.

8. Particle Systems: There are 3 instences of particals, 2 are quite diffrent.

Enemy bullet hit/explosion: a blood red spark that scrapes off the player when an enemy bullet
hits him. Uses a medium amount of particals

Player bullet trail: A thin germ trail of greenish-yellow ooze that follows player bullets, gets
larger the more powerful the bullet is. Uses a low amount of particals

Player bullet hit/explosion: A yellowish-green color swap of the enemy bullet hit/explosion

9. UI: the player HUD scales with camera zoom and player movment. Displays a timer, 
current health, max health, and ammo count for the special shot.

10. Advanced method: Steering Behaviors, all enemys have the chase behavoir.
The white bloodcell also as the flee bahvoir, implimentations are discused above in "2. Enemys"

11. Code readability and organization:
We left comments requently, and where possible organized code into functions/methods.

12. Bonus: Lmao hopfully we can get this done




Credits:
All art either provided by Profesor or created by the group for this project.