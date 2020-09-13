var keypress = require('keypress');
var exec = require('child_process').exec;
// make `process.stdin` begin emitting "keypress" events
keypress(process.stdin);
 
// listen for the "keypress" event

process.stdin.on('keypress', function (ch, key) {
 	console.log(key.sequence);
  	if (key && key.ctrl && key.name == 'c') {
    	process.stdin.pause();
	}

	exec('keyboard-driver.exe'); // input key.sequence
});

process.stdin.setRawMode(true);
process.stdin.resume();
