const electron = require('electron');
const url = require('url');
const path = require('path');
// const fabric = require('fabric').fabric;
const {app, BrowserWindow, Menu} = electron;
let mainWindow;

//listen for the app to be ready.
app.on('ready', function(){
    mainWindow = new BrowserWindow({
        width:300,
        height:200,
        title:'Add File',
        webPreferences:{
            nodeIntegration:true,
            contextIsolation:false
        }
    });
    mainWindow.loadURL(url.format({
        pathname:path.join(__dirname, 'mainWindow.html'),
        protocol:'file:',
        slashes:true
    }))

})
