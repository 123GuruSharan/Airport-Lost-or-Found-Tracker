# CPP Projects - Web Server Implementations

This repository contains various implementations of web servers using C++ and Node.js, along with HTML frontend pages for a simple item reporting and searching system.

## Project Overview

The project demonstrates different approaches to building web servers:
- C++ implementations using Crow and cpp-httplib libraries
- Node.js implementation using Express.js
- HTML/CSS frontend for user interaction

## Difficulties Faced and Solutions

### 1. Setting up C++ Development Environment on Windows

**Difficulty:** Installing and configuring C++ compilers and libraries on Windows was challenging, especially for network programming with ASIO.

**Solution:**
- Downloaded and installed MinGW-w64 compiler suite (mingw-w64-13.2.0.zip)
- Extracted ASIO library (asio-1.28.0.zip) for asynchronous I/O operations
- Used vcpkg package manager for managing C++ dependencies
- Configured include paths and library linking in build scripts

### 2. Integrating Multiple Web Server Libraries

**Difficulty:** Choosing and integrating different C++ web server libraries (Crow, cpp-httplib) while ensuring compatibility with the Windows environment.

**Solution:**
- Implemented separate versions using different libraries:
  - `web_server.cpp` using cpp-httplib
  - `web_server_crow.cpp` using Crow framework
- Maintained consistent API endpoints across implementations
- Used CMake for build configuration where applicable

### 3. Cross-Platform Compatibility Issues

**Difficulty:** Ensuring code compiles and runs correctly across different environments, particularly Windows-specific path handling and library linking.

**Solution:**
- Used conditional compilation for platform-specific code
- Standardized on MinGW for consistent compilation
- Implemented fallback mechanisms for missing dependencies

### 4. Dependency Management

**Difficulty:** Managing complex dependency chains for C++ libraries, especially network-related ones.

**Solution:**
- Utilized vcpkg for automated dependency resolution
- Manually downloaded and integrated ASIO library
- Created modular code structure to isolate library dependencies

### 5. Concurrent Server Implementations

**Difficulty:** Maintaining multiple server implementations (C++ and Node.js) with consistent functionality.

**Solution:**
- Developed a Node.js Express server (`server.js`) as a reference implementation
- Implemented equivalent functionality in C++ versions
- Used common HTML frontend across all server implementations

## Technologies Used

- **C++:**
  - Crow web framework
  - cpp-httplib
  - ASIO for networking
  - MinGW-w64 compiler

- **Node.js:**
  - Express.js web framework
  - body-parser for request parsing

- **Frontend:**
  - HTML5
  - CSS3
  - Vanilla JavaScript

## Running the Project

### Node.js Server (Recommended for Development)
```bash
npm install
npm start
```
Server runs on http://localhost:18080

### C++ Servers
Compile and run the respective C++ files using MinGW:
```bash
g++ -o web_server web_server.cpp -I/path/to/asio/include
./web_server
```

## API Endpoints

- `POST /report` - Report a new item
- `POST /search` - Search for items by ID or description

## File Structure

- `server.js` - Node.js Express server
- `web_server.cpp` - C++ server using cpp-httplib
- `web_server_crow.cpp` - C++ server using Crow
- `*.html` - Frontend pages
- `styles.css` - CSS styling
- `asio-*/` - ASIO library
- `cpp-httplib/` - HTTP library for C++
- `Crow/` - Crow web framework
- `mingw64/` - MinGW compiler
- `vcpkg/` - Package manager
