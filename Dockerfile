# --- Stage 1: Build Environment ---
FROM gcc:latest AS builder

# Install CMake and dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    libboost-system-dev \
    libboost-regex-dev \
    libboost-date-time-dev \
    libboost-program-options-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

# Copy and Build 'served' library from local source
WORKDIR /libs
COPY served-master ./served
WORKDIR /libs/served
RUN mkdir build && cd build && \
    cmake .. && \
    make -j$(nproc) && \
    make install

# Copy your project source code
WORKDIR /app
COPY . .

# Build your Rubik's Cube Solver
RUN rm -rf build && mkdir build && cd build && \
    cmake .. && \
    make -j$(nproc)

# --- Stage 2: Runtime Environment ---
FROM ubuntu:24.04

# Install runtime dependencies (Shared libraries)
RUN apt-get update && apt-get install -y --no-install-recommends \
    libboost-system1.83.0 \
    libstdc++6 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy the compiled executable from the builder stage
COPY --from=builder /app/build/cpprestserver .

# Copy the served library from builder stage
COPY --from=builder /usr/local/lib/libserved.so* /usr/local/lib/

# Copy boost libraries from builder stage
COPY --from=builder /usr/lib/x86_64-linux-gnu/libboost_*.so.* /usr/lib/x86_64-linux-gnu/

# Update library cache
RUN ldconfig

# Copy heuristics data from builder stage
COPY --from=builder /app/resources/heuristics ./heuristics

# Expose the port your REST server uses (usually 8080 or 8000)
EXPOSE 8080

# Run the server
CMD ["./cpprestserver"]