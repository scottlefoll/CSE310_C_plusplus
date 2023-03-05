# Minions Adventure OOP C++ Game

# Overview

Minions Adventure is a game that demonstrates basic object-oriented programming in C++. The game involves a character moving around to collect coins while avoiding enemies. The player's score increases when they collect a coin, and the score is reset to zero when they collide with an enemy. Use the Up, Down, Left, and Right arrow keys to move the Minion.

It is intended to demonstrate the creator's first program using C++, and to illustrate the features, structures, and syntax of C++.

# Development Environment

The program is written in C++ using the g++ compiler, and and VS Code. The environment was Windows 10 Professional on an intel desktop.

## Requirements

Dependencies:
C++11 or later
SFML library
cstdlib
ctime
string
vector

## Image and font files: 
(The game requires 3 image files and a font file, and these should be located in the same folder/location as the minions.exe application file.)
character_x.png
coin_x.png
enemy_1_x.png
arial.ttf

# Useful Websites

- [Programmiz C++](https://www.programiz.com/cpp-programming)
- [W3 Schools C++](https://www.w3schools.com/cpp/)
- [Tutorialspoint C++](https://www.tutorialspoint.com/cplusplus/index.htm)
- [Codecademy](https://www.codecademy.com/learn/learn-c-plus-plus)
_ [Geeks for Geeks C++](https://www.geeksforgeeks.org/c-plus-plus/)
- [Wiki C++](https://en.wikipedia.org/wiki/C%2B%2B)

# Future Work

These are items for future development and enhancement:

- Make several levels for the game.
- Make a file that allows the number of enemies, coins, and the speeds to be set by the user.
- Add sound.


## How to Play
Use the arrow keys to move the character.
Collect coins to increase your score.
Avoid enemies, as colliding with one will reset your score.

## Code Structure
The game is divided into several classes, each representing a game object:

## Player: Represents the game's main character.
Token: Represents the coins the player collects.
TokenController: is the controlling class for the group of tokens. It takes care of moving them, resetting them and tracking collisions.
Enemy: Represents the obstacles the player must avoid.
EnemyController: is the controlling class for the group of enemies. It takes care of moving them, resetting them and tracking collisions.
Score: Represents the player's score.


{Provide a link to your YouTube demonstration. It should be a 4-5 minute demo of the software running and a walkthrough of the code. Focus should be on sharing what you learned about the language syntax.}

[Software Demo Video](http://youtube.link.goes.here)
