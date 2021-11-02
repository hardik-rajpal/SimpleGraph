############################
DSA Project by Hardik Rajpal
############################

I have (with permission) done a project different from the two screensaver
alternatives offered in the announcement. This is a data structure library
for (undirected for now) Graphs in C++. It comes with an Electron-based
renderer for graphs created using the library. The two programs communicate
via local socket server (c++) and client (js) objects.

The demo suggested by Prof. Raman was an animation of a bfs. That is not ready
yet.

Supported platforms: Windows 10 64bit.

Graph.h: Contains list of functionality (with few definitions) and classes.

Graph.cpp: Contains implementation of SimpleGraph, Edge, Node and ServerSocket.

Graph.tpp: Contains implementations of functions using c++ templates (they can't be
            implemented in regular .cpp files.)

server.cpp:Contains implementation for ServerSocket.cpp using winsock2 API.

main.cpp: Example program using the library.

testing.cpp: Secondary testing file. (Not relevant to the project's demo).

Makefile: makefile for Windows.


Renderer in ./fabext:
    client.js: contains functions used to connect to socket server and communicate with it.

    fabric.js: contains rendering functions and data structures.

    fabric.min.js: 3rd party canvas library file.

    main.js: main file for Electron application.

    mainWindow.html: Window design for Electron application.

    package.json and package-lock.json: node js configuration files.
