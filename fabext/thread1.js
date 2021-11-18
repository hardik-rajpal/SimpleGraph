const {exec} = require('child_process');
setTimeout(()=>{
    process.exit();
}, 1000);
// console.log("about to launch")
process.chdir('.\\fabext');
// console.log()
setTimeout(()=>{
    exec("node thread2.js " + process.argv[2]);
}, 0)
