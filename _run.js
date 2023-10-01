const PATH      = require("./_env_path.js")
const {exec}    = require("child_process")

const command   = `${PATH.PATH_TO_EXECUTABLE}`
exec(command, function (error, stdout, stderr) {
    console.log('stdout: ' + stdout);
    console.log('stderr: ' + stderr);
    if (error !== null) {
         console.log('exec error: ' + error);
    }
})