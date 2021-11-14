function includeJs(jsFilePath) {
    var js = document.createElement("script");
    js.type = "text/javascript";
    js.src = jsFilePath;
    document.body.appendChild(js);
}
function synclooper(){
    if(global.client.writable){
        syncData();
        setTimeout(()=>{synclooper()}, 3000);
    }
}
function exportIMG(){
    let img = global.canvas.toDataURL("image/png");
    let a = document.getElementById("a");
    a.setAttribute('download', 'Graph.png')
    a.setAttribute('href', img.replace("image/png", "image/octet-stream"))
    a.click();
}
function sendCommand(cmd){
    //cmd and data distinguished by length.
    //cmd < 20.
    if(global.client.writable){
        client.write(cmd);
    }
}
function exportMinTXT(){
    sendCommand("expmintxt");
}
function syncData(){
    let vdata = JSON.stringify(filterForServer(global.canvas.renderMeta))
    global.client.write(vdata)
}
function exportJSON(){
    sendCommand("expjson");
}
function setStatus(status){
    document.querySelector('#status').innerHTML = status
}
function resetCanvas(canvas){
    let renderMeta = {
        radius:canvas.renderMeta.radius,
        radroot:Math.SQRT1_2*canvas.renderMeta.radius,
        V:{},
        E:{},
    }
    canvas.renderMeta = renderMeta;
    canvas.clear();
    canvas.backgroundColor = '#eef';
}
function connect(PORT,HOST){
    global.client.connect(PORT, HOST, function(){
        setStatus("Connected");
        console.log("Connected Host");
        resetCanvas(global.canvas);
    })
}
function main(){
    let radius = 7.5;
    let radroot = Math.SQRT1_2*radius;
    const canvas = initCanvas("canvas");
    canvas.on('object:moving', nodeDrag);
    canvas.on('mouse:over', displayData);
    canvas.on('mouse:out', hideData);
    // console.log(canvas)
    let renderMeta = {
        radius:radius,
        radroot:radroot,
        V:{},
        E:{},
    }
    canvas.renderMeta = renderMeta;
    global.canvas = canvas


    const net = require('net');
    const HOST = '127.0.0.1';
    const PORT = 7171;
    var client = new net.Socket();
    global.client = client;
    global.datarec = ""
    try{
        connect(PORT, HOST);
    }
    catch(error){
        setStatus('Disconnected<button class="btn btn-primary btn-sm" onclick=\"connect(7171,\'127.0.0.1\')\">Reconnect</button>');
        return;
    }
    
    
    client.on('data', function(data){
        setStatus("Rec.");
        recon = String.fromCharCode.apply(null,data.toJSON().data)
        if(recon=="paused"){
            setStatus("Connected:Paused <button class=\"btn btn-primary btn-sm\" onclick=\"syncData();sendCommand('play')\">Play</button>");
            return;
        }
        global.datarec +=recon
        console.log(global.datarec.substr(0,global.datarec.length-1))
        if(global.datarec[global.datarec.length-1]=='0'){

            parsedata = JSON.parse(global.datarec.substr(0,global.datarec.length-1))
            console.log(parsedata);
            // resetCanvas(canvas);
            render(parsedata,canvas);
            global.datarec = ""
            let Vdata = filterForServer(canvas.renderMeta)
            let dat = JSON.stringify(Vdata)
            // console.log(dat)
            client.write(dat)
        }
        setStatus("Connected");
    })
    client.on('error', (er)=>{
        client.destroy();
        setStatus("Disconnected<button class=\"btn btn-primary btn-sm\" onclick=\"connect(7171,'127.0.0.1')\">Reconnect</button>");
    })
    global.client = client
    // setTimeout(()=>{
    //     synclooper();
    // }, 3000)
}
main()

