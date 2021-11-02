graphws: main.cpp Graph.cpp server.cpp
	g++ main.cpp Graph.cpp server.cpp -lws2_32 -o gs
graph: main.cpp Graph.cpp
	g++ main.cpp Graph.cpp -o g
nodemod:
	cd fabext
	npm i
render: fabext/client.js fabext/fabric.js fabext/main.js fabext/mainWindow.html
	cd fabext
	npm start