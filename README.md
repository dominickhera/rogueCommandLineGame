# rogueCommandLineGame

=
a4
5/3/16
dominick hera
======================

======
to run
======
./bin/rogue ./assets/hard.txt

==========
to compile
==========
type 'make' to run the makeFile

====================
known limitations
====================
- hallway offsets are messed up and some print far off the screen
- combat seems to only work on enemies within the first room but fails to work in any other room
- when transitioning from room to hallway, it turns the doorway into a # character
- when picking up an item, the area of the item becomes a # character
- hallways designed for the lower rooms runs directly over top level rooms
- bats will move around randomly but will spawn again after dying
- unkilled bats will move around freely until they hit the wall in which they proceed to only go up and down but are still able to be killed
- only south facing doorways seem to work, all other doorways seem to be messed up by the offset number for the rooms, or be printed somewhere far from where they are needed
- picking up equiptment or items doesn't print the coded notification
- only bats will listen to the patrol calls, none of the other enemies will move around

=======
testing
=======
- bat enemy was spawning with 50 health, turns out it was a typing error in the code 
