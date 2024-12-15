import ancillaire from "./index.cjs";

const isNotUint = (v) => typeof v !== 'number' || v % 1 !== 0 || v < 0;

function version() {
    return ancillaire.version();
}
function sendFd(socketFd, fd) {
    if (isNotUint(socketFd)) throw new Error('socketFd must be an unsigned int');
    if (isNotUint(fd)) throw new Error('fd must be an unsigned int');
    return ancillaire.sendFd(socketFd, fd);
}
function recvFd(socketFd) {
    if (isNotUint(socketFd)) throw new Error('socketFd must be an unsigned int');
    return new Promise((cb) => ancillaire.recvFd(socketFd, cb));
}

export default { version, sendFd, recvFd };
