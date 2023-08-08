# EndlessRunner

A simple endles runner. Move with WASD and jump with space. Try and stay on top of the platforms.

# Part1
I didn't acive much yet, just a simple platfom spawner and moving platform.
The moving platform is configuarble (in code) but is right now tigthly coupled with the spawer.

# Part2 
I made all requirements for part 1. I didn't make the requerments for part 2 since it's hard to fit in to the design. It isn't clear when you have cleared a obstacle becouse you can move backwards and forwards and Unreals local multiplayer is broken in the latest version and it would be realy hard to make a AI jumping between the platforms.

I didn't have any major bugs to fix that I found.

A design choice I made last minute that I'm not happy with was to reuse my platform spawner to spawn obstacles. I shuld have made a obstacle spawner with a common baseclass with Platformspawner and also mad a baseclass for MovingPlatform and Obstacle.

# Extra
Made a simpe AI companion and exploding obstacles to comply with spec
