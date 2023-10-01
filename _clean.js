const PATH      = require("./_env_path.js")
const {exec}    = require("child_process")

const command   = `cd ${PATH.BUILD} && ${PATH.MAKE} clean -j16 && cd ..`
exec(command, function (error, stdout, stderr) {
    console.log('stdout: ' + stdout);
    console.log('stderr: ' + stderr);
    if (error !== null) {
         console.log('exec error: ' + error);
    }
})