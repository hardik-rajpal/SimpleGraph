function includeJs(jsFilePath) {
    var js = document.createElement("script");
    js.type = "text/javascript";
    js.src = jsFilePath;
    document.body.appendChild(js);
}
function syncData(){
    let vdata = JSON.stringify(filterForServer(global.canvas.renderMeta))
    global.client.write(vdata)
}
function main(){
    let radius = 15;
    let radroot = Math.SQRT1_2*radius;
    
    const canvas = initCanvas("canvas");
    canvas.on('object:moving', nodeDrag);
    console.log(canvas)
    let renderMeta = {
        radius:radius,
        radroot:radroot,
        V:{},
        E:{},
    }
    canvas.renderMeta = renderMeta;
    // console.log(renderMeta.canvas);
    global.canvas = canvas
    const net = require('net');
    const HOST = '127.0.0.1';
    const PORT = 7171;
    var client = new net.Socket();
    client.connect(PORT, HOST, function(){
        console.log("Connected Host");
    })
    client.on('data', function(data){
        recon = String.fromCharCode.apply(null,data.toJSON().data)
        parsedata = JSON.parse(recon)
        render(parsedata,canvas);
        let Vdata = filterForServer(canvas.renderMeta)
        // let Vdata = canvas.renderMeta.V;
        // console.log(Vdata)
        let dat = JSON.stringify(Vdata)
        client.write(dat)
    })
    global.client = client
    // setTimeout(()=>{
    //     client.write("Hi");
    // }, 0)

}
main()

