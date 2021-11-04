graphws: mainpath.cpp Graph.cpp Server.cpp
	echo #define SERVERUSED > config.h
	g++ mainpath.cpp Server.cpp Graph.cpp  -lws2_32 -o gs
graph: mainpath.cpp Graph.cpp
	echo #define SERVERNOTUSED > config.h
	g++ mainpath.cpp Graph.cpp -o g
bfs: bfsanim.cpp Graph.cpp Server.cpp
	echo #define SERVERUSED > config.h
	g++ bfsanim.cpp Graph.cpp Server.cpp -lws2_32 -o bfs
dfs:  dfsanim.cpp Graph.cpp Server.cpp
	echo #define SERVERUSED > config.h
	g++ dfsanim.cpp Graph.cpp Server.cpp -lws2_32 -o dfs
nodemod:
	cd fabext
	npm i
render: fabext/client.js fabext/fabric.js fabext/main.js fabext/mainWindow.html
	cd fabext
	npm start
test: testing.cpp Graph.cpp
	echo #define SERVERUSED > config.h
	g++ testing.cpp Graph.cpp Server.cpp -l ws2_32 -o t