const PATH      = require("./_env_path.js")
const process   = require("child_process")

const command   = `cd ${PATH.BUILD} && ${PATH.MAKE} clean -j16 && cd ..`
const qmake_process = process.spawn(command, {shell: true});
qmake_process.stdout.on("data", data => {
  // Process and display the log output
  console.log(`${data}`);
});

qmake_process.stderr.on("data", data => {
  // Display any errors from the command
  console.error(`Error: ${data}`);
});

qmake_process.on("close", code => {
  // Capture the exit code of the command
  console.log(`Command exited with code ${code}`);
});
