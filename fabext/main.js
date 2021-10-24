const electron = require('electron');
const url = require('url');
const path = require('path');
// const fabric = require('fabric').fabric;
const {app, BrowserWindow, Menu} = electron;
let mainWindow;

//listen for the app to be ready.
app.on('ready', function(){
    mainWindow = new BrowserWindow({});
    mainWindow.loadURL(url.format({
        pathname:path.join(__dirname, 'mainWindow.html'),
        protocol:'file:',
        slashes:true
    }))
    //Build menu from tempalte
    const mainMenu = Menu.buildFromTemplate(mainMenuTemplate);
    Menu.setApplicationMenu(mainMenu);
})

const mainMenuTemplate = [
    {
        label:'File',
        submenu:[
            {
                label:'Add Item',
                click(){
                    createAddWindow();
                }
            },
            {
                label:'Quit',//shortcuts:
                accelerator:  process.platform=='darwin' ? 'Command+Q':'Ctrl+Q', 
                click(){
                    app.quit();
                }
            }
        ]
    }
]