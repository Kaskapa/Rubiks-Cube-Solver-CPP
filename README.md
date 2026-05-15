# Rubik's Cube Solver API

A high-performance RESTful API for solving 3x3 Rubik's Cubes, implemented in C++ using the [Served](https://github.com/meltwater/served) web framework. This project explores search algorithms and their real-world applications, originally developed as a qualification project.

## Features

- **Fast Solver:** Leverages C++ efficiency to find cube solutions quickly.
- **WCA Notation:** Accepts cube states in standard World Cube Association scramble notation.
- **RESTful API:** Easy-to-use HTTP endpoints for integration with web or mobile apps.
- **Lightweight:** Minimal overhead thanks to the `served` library and Boost.ASIO.

## Tech Stack

- **Language:** C++11 or higher.
- **Web Framework:** Served.
- **Asynchronous I/O:** Boost.ASIO.
- **Build System:** CMake.

## Building and Running

1. **Build the Docker Image:**
   ```bash
   docker build -t rubiks-solver .
   ```

2. **Run the Container:**
   ```bash
   docker run -p 8123:8123 rubiks-solver
   ```
   *Note: This maps the internal server port to your local machine. Ensure the port matches your `cpprestserver.cpp` configuration.*

## API Usage

The solver typically accepts the cube state as a string parameter.

**Example Request:**
```bash
curl http://localhost:8123/solve?state="R U R' U'"
```

## Documentation
For a detailed analysis of the algorithm and implementation, please refer to the Technical Documentation PDF.
