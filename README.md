Link to Demo Video: https://drive.google.com/file/d/1Ofxm5Yiq_MVEymQtTvcS3U_DscEelxgl/view?usp=sharing
Link to Code with a decent Directory structure: https://drive.google.com/file/d/1_SDPt3bI8quSSVpK5ofzaU49wOuTl8ce/view?usp=sharing
(It's size was > 2.5MB, even without the BGM)

############################
SimpleGraph: DSA Project by Hardik Rajpal
############################

I have (with permission) done a project different from the two screensaver
alternatives offered in the announcement. This is a data structure library
for (undirected for now) Graphs in C++. It comes with an Electron-based
renderer for graphs that are created using the library. The two programs
communicate via local socket server (c++) and client (js) objects.

The demo suggested by Prof. Raman was an animation of a bfs.

Supported platforms: Windows 10 (64bit).

Graph.h: Contains list of functionality (with few definitions) and classes.

Server.h: Contains list of functionality for ServerSocket class.

config.h: Used to allow building with and without the server implementation.

Graph.cpp: Contains implementation of SimpleGraph methods.

Graph.tpp: Contains implementations of functions using c++ templates (they can't be
            implemented in regular .cpp files.)

Server.cpp:Contains implementation for ServerSocket.cpp using winsock2 API.

Static.cpp: Contains auxiliary functions like serializers and parsers, and
            templates for standard graphs.

Makefile: makefile for Windows.


Renderer in ./fabext:
    client.js: contains functions used to connect to socket server and communicate with it.

    fabric.js: contains rendering functions and data structures.

    thread1.js: This file is called by initServer() from c++. It calls thread2.js

    thread2.js: This in turn launchs the renderer program.

    fabric.min.js: 3rd party canvas library file.

    main.js: main file for Electron application.

    mainWindow.html: Window design for Electron application.

    package.json and package-lock.json: node js configuration files.


Setup (Windows 10, 64bit only):
    RF = root folder contains fabext, GS, include, src, Makefile
    In RF/fabext:
        run: "npm i" in the terminal (of the right folder) to install node packages.
        run: "npm start" to test the renderer. If version-based errors arise, go S.O.
    Once the renderer is working, you can directlly use the makefile with "nmake."
    If the renderer doesn't work, you can use the library by changing nmake commands to
    echo SERVERNOTUSED > ./include/config.h
    ...compilation command.