<div align="center">

# Mauricio el Salta Muros

### A 2D Mexican-Inspired Platformer Made with C and Raylib

</div>

---

## About the Game

**Mauricio el Salta Muros** is a 2D platformer game developed in **C** using the **Raylib** library.

The game follows Mauricio through different Mexican-inspired environments, combining classic platformer mechanics with cultural references, enemies, collectibles, music, animations, and an interactive story guided by Quetzalcóatl.

The player must run, jump, crouch, avoid enemies, collect items, and advance through different levels inspired by Mexican culture and locations.

---

## Main Features

- 2D platformer gameplay
- Mexican-inspired environments
- Main menu system
- Tutorial section
- Pause menu
- Save and load game system
- Customizable controls
- Volume configuration
- Character animations
- Enemies and obstacles
- Collectible items
- Background music
- Sound effects
- Story elements with Quetzalcóatl
- Multiple game states
- File handling for saved progress

---

## Technologies Used

- C
- Raylib
- Code::Blocks
- GCC Compiler

---

## Project Structure

<pre>
Mauricio el salta muros/
│
├── audio/
│   ├── item.mp3
│   ├── jump.mp3
│   ├── level1_music.mp3
│   ├── music.mp3
│   ├── powerup.wav
│   └── writing.wav
│
├── backgrounds/
│   ├── reformaday.png
│   ├── reformanight.png
│   ├── tenochtitlan.png
│   ├── chicheniztanoon.png
│   └── other background assets
│
├── sprites/
│   ├── mauricio.png
│   ├── mauricio2.png
│   ├── quetzalcoatl_right.png
│   ├── coin.png
│   ├── vida.png
│   └── other sprite assets
│
├── src/
│   ├── main.c
│   ├── Raylib.cbp
│   └── partida_guardada.dat
│
└── README.md
</pre>

---

## Controls

Default controls:

| Action | Key |
|---|---|
| Move Left | A |
| Move Right | D |
| Jump | Space |
| Crouch | Left Control |
| Run | Left Shift |
| Select Option | Enter |
| Navigate Menu | W / S |
| Go Back | Backspace |

The game also includes an options menu where the player can customize the controls.

---

## How to Run

### Option 1: Run with Code::Blocks

1. Install **Raylib**.
2. Open the project file:

<pre>
src/Raylib.cbp
</pre>

3. Make sure Raylib is correctly installed and configured on your computer.
4. Build and run the project from Code::Blocks.

---

### Option 2: Compile Manually

Make sure **Raylib** and **GCC** are installed.

Then compile the project using:

<pre>
gcc src/main.c -o MauricioElSaltaMuros -lraylib -lopengl32 -lgdi32 -lwinmm
</pre>

Run the game with:

<pre>
./MauricioElSaltaMuros
</pre>

On Windows, the executable may be generated as:

<pre>
MauricioElSaltaMuros.exe
</pre>

---

## Requirements

- Windows
- GCC Compiler
- Raylib installed
- Code::Blocks recommended
- All assets must remain in their original folders:
  - `audio/`
  - `backgrounds/`
  - `sprites/`

---

## Gameplay Summary

The game starts with a main menu where the player can start a new game, load a saved game, access options, or exit.

During the adventure, Mauricio receives guidance from Quetzalcóatl and travels through different Mexican-inspired scenarios. The player must use movement skills, timing, and strategy to avoid enemies, collect items, and continue progressing through the game.

---

## Save System

The game includes a save system that stores the player's progress using the file:

<pre>
partida_guardada.dat
</pre>

This allows the player to continue from a saved point instead of starting from the beginning.

---

## Educational Purpose

This project was developed as an academic programming project to practice and demonstrate knowledge in:

- Programming in C
- Game development fundamentals
- Raylib library usage
- Collision detection
- Sprite animation
- User input handling
- Game states
- Menu systems
- Audio management
- File handling
- Basic software organization

---

## Assets

The project includes different assets such as:

- Character sprites
- Background images
- Enemy sprites
- Collectible sprites
- Sound effects
- Background music
- Interface elements

These assets are used to create a more complete and interactive game experience.

---

## Author

Developed by **Marlon Molina**.

---

## License

This project was created for educational purposes.

You may use it as a learning reference or modify it for academic and personal practice.
