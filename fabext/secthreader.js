const {exec} = require('child_process');
setTimeout(()=>{
    process.exit();
}, 5000);
setTimeout(()=>{
    exec(".\\simgra-win32-x64\\simgra.exe dmyvar " + process.argv[2]);
}, 2000)
