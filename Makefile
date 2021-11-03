graphws: mainpath.cpp Graph.cpp Server.cpp
	g++ mainpath.cpp Server.cpp Graph.cpp  -lws2_32 -o gs
graph: mainpath.cpp Graph.cpp
	g++ mainpath.cpp Graph.cpp -o g
nodemod:
	cd fabext
	npm i
render: fabext/client.js fabext/fabric.js fabext/main.js fabext/mainWindow.html
	cd fabext
	npm start