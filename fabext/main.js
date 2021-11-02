const electron = require('electron');
const url = require('url');
const path = require('path');
// const fabric = require('fabric').fabric;
const {app, BrowserWindow, Menu} = electron;
let mainWindow;

//listen for the app to be ready.
// app.commandLine.appendArgument('--allow-insecure-localhost', 'true');

// app.commandLine.appendSwitch('ignore-certificate-errors', 'true');
// app.commandLine.appendSwitch('ignore-ssl-errors', 'true');
app.commandLine.appendArgument('--ignore-certificate-errors-spki-list');
app.on('ready', function(){
    mainWindow = new BrowserWindow({
        width:800,
        height:800,
        title:'Add File',
        webPreferences:{
            nodeIntegration:true,
            contextIsolation:false,
            webSecurity:false,
            allowDisplayInsecureContent:true,
            allowRunningInsecureContent:true
        }
    });
    mainWindow.loadURL(url.format({
        pathname:path.join(__dirname, 'mainWindow.html'),
        protocol:'file:',
        slashes:true
    }))

})
