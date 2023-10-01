const PATH      = require("./_env_path.js")
const {exec}    = require("child_process")

const command   = `if NOT exist ${PATH.BUILD} mkdir ${PATH.BUILD} && cd ${PATH.BUILD} && ${PATH.QMAKE} ${PATH.PROFILE} "CONFIG+=${PATH.EXTRA}" && ${PATH.MAKE} -j16 && cd ../`
exec(command, function (error, stdout, stderr) {
    console.log('stdout: ' + stdout);
    console.log('stderr: ' + stderr);
    if (error !== null) {
         console.log('exec error: ' + error);
    }
})