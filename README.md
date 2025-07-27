# Rubik's Cube Solver API - C++
A RESTful API for solving Rubik's Cubes, implemented in C++ with served. Based on a previous solver created in Python: [Kaskapa/Rubiks-cube-solver-3x3: Trying to understand the rubik's cube solving method by Herbert Kociemba.](https://github.com/Kaskapa/Rubiks-cube-solver-3x3)

## Features
- HTTP API endpoint for cube solving
- Accepts cube state in standard notation
- Returns solution in standard move notation
- Lightweight and fast C++ implementation

## Cube Notation
Uses standard cube notation:
- Faces: U (Up), D (Down), L (Left), R (Right), F (Front), B (Back)
- Moves: X (clockwise), X' (counter-clockwise), X2 (180°)

## Purpose
Started as a pet project to explore search algorithms and their use cases in real life, then went in too deap and made it as my qualifications project for my degree.

Documenation: [Rubiks-Cube-Solver-CPP/Veveris_KVD_Rubika_kubika_analizators.pdf at main · Kaskapa/Rubiks-Cube-Solver-CPP](https://github.com/Kaskapa/Rubiks-Cube-Solver-CPP/blob/main/Veveris_KVD_Rubika_kubika_analizators.pdf)
