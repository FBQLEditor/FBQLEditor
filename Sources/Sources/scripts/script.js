function log(data) {
    log_output.insertPlainText(data + "\n")
}

function clear() {
    log_output.clear()
}

function TOutput() {}

TOutput.prototype.clear = clear
TOutput.prototype.log = log

var console = new TOutput()
