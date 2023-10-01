const PATH = require("./_env_path.js");
const process = require("child_process");

var commands = [
  `if NOT exist ${PATH.BUILD} mkdir ${PATH.BUILD}`,
  `cd ${PATH.BUILD} && pwd && ${PATH.QMAKE} ${PATH.PROFILE} "CONFIG+=${PATH.EXTRA}" && ${PATH.MAKE} -j16 && cd ..`
];

process.execSync(commands[0]);
const qmake_process = process.spawn(commands[1], {shell: true});
qmake_process.stdout.on("data", data => {
  // Process and display the log output
  console.log(`Log output: ${data}`);
});

qmake_process.stderr.on("data", data => {
  // Display any errors from the command
  console.error(`Error: ${data}`);
});

qmake_process.on("close", code => {
  // Capture the exit code of the command
  console.log(`Command exited with code ${code}`);
});
