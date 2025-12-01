FROM ubuntu:22.04

# Install dependencies
RUN apt update && apt install -y \
    g++ \
    cmake \
    make \
    libboost-all-dev \
    wget \
    unzip \
    && rm -rf /var/lib/apt/lists/*

# Install standalone ASIO
RUN wget https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-28-0.zip -O asio.zip \
    && unzip asio.zip \
    && cp -r asio-asio-1-28-0/asio/include/asio /usr/local/include/ \
    && rm -rf asio.zip asio-asio-1-28-0

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
