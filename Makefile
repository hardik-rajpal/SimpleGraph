graphws: mainpath.cpp Graph.cpp Server.cpp
	echo #define SERVERUSED > config.h
	g++ mainpath.cpp GS/Server.cpp GS/Static.cpp GS/Graph.cpp  -lws2_32 -o gs
graph: mainpath.cpp Graph.cpp
	echo #define SERVERNOTUSED > config.h
	g++ mainpath.cpp GS/Graph.cpp GS/Static.cpp -o g
bfs: src/bfsanim.cpp GS/Graph.cpp GS/Server.cpp
	echo #define SERVERUSED > ./include/config.h
	g++ src/bfsanim.cpp GS/Graph.cpp GS/Static.cpp GS/Server.cpp -lws2_32 -o build/bfs
dfs:  src/dfsanim.cpp GS/Graph.cpp GS/Server.cpp
	echo #define SERVERUSED > ./include/config.h
	g++ src/dfsanim.cpp GS/Graph.cpp GS/Static.cpp GS/Server.cpp -lws2_32 -o build/dfs
col:  src/collatz.cpp GS/Graph.cpp GS/Server.cpp
	echo #define SERVERUSED > ./include/config.h
	g++ src/collatz.cpp GS/Graph.cpp GS/Static.cpp GS/Server.cpp -lws2_32 -o build/col
nodemod:
	cd fabext
	npm i
render: fabext/client.js fabext/fabric.js fabext/main.js fabext/mainWindow.html
	cd fabext
	npm start
test: src/testing.cpp GS/Graph.cpp GS/Server.cpp GS/Static.cpp
	echo #define SERVERUSED > ./include/config.h
	g++ -I'./include' src/testing.cpp GS/Graph.cpp GS/Static.cpp GS/Server.cpp -l ws2_32  -o build/t
final: src/final.cpp GS/Graph.cpp GS/Server.cpp GS/Static.cpp
	echo #define SERVERUSED > ./include/config.h
	g++ -I'./include' src/final.cpp GS/Graph.cpp GS/Static.cpp GS/Server.cpp -l ws2_32  -o build/f
extract: src/extract.cpp GS/Graph.cpp GS/Server.cpp GS/Static.cpp
	echo #define SERVERUSED > ./include/config.h
	g++ -I'./include' src/extract.cpp GS/Graph.cpp GS/Static.cpp GS/Server.cpp -l ws2_32  -o build/e