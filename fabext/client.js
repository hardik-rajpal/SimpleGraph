const net = require('net');
var HOST = '127.0.0.1';
var PORT = 7171;
var client = new net.Socket();
client.connect(PORT, HOST, function(){
    console.log("Connected Host");
})

client.on('data', function(data){
    recon = String.fromCharCode.apply(null,data.toJSON().data)
    console.log(JSON.parse(recon).V[0])
})