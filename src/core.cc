#include <gutils.h>

void die(string const msg, int ec) {
    std::cerr << "[ERROR] " << msg << std::endl;
    exit(ec);
}

void die(string const msg) {
    die(msg, 1);
}
