# Maze Project

Welcome to the Maze Project! This project is aimed at creating a 3D maze game using raycasting techniques. You will embark on an exciting journey of developing a 3D maze game where the camera navigates through walls.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Resorces](#resorces)

## Overview

The goal of this project is to create a 3D maze game using raycasting. You'll develop a game where the camera navigates through walls, starting with SDL2 basics and advancing to textures, enemies, and effects.

## Features

- Create a window with SDL2
- Use raycasting to draw walls
- Handle camera rotation and movement
- Collision detection
- Map parsing from a file
- Display the map on the window
- Include weapons
- Handle multiple events in the same frame

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/Ibrahim-Naguib/maze.git
   ```
2. Navigate to the project directory:
   ```sh
   cd maze
   ```
3. Install the necessary dependencies. Make sure you have `SDL2` installed. You can install it using your package manager. For example, on Ubuntu:
   ```sh
   sudo apt-get install libsdl2-dev
   ```
4. Compile the project using `Makefile`:
   ```sh
   make
   ```

## Usage

Run the executable created after compilation:

```sh
./Maze map.txt
```

## Resorces

### Raycasting tutorials

https://lodev.org/cgtutor/raycasting.html

### SDL2 tutorials

https://lazyfoo.net/tutorials/SDL/index.php
