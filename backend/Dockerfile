FROM ubuntu:22.04

# Install dependencies
RUN apt update && apt install -y \
    g++ \
    cmake \
    make \
    libboost-all-dev \
    && rm -rf /var/lib/apt/lists/*

# Set workdir to /app
WORKDIR /app

# Copy ONLY the backend folder
COPY backend/ .

# Build app
RUN mkdir build && cd build && cmake .. && make

# Expose the Render port
ENV PORT=8080
EXPOSE 8080

# Start the app
CMD ["./build/app"]
