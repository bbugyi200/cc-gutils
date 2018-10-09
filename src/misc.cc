#include <gutils.h>

void die(const std::string msg, int ec) {
    std::cout << msg << std::endl;
    exit(ec);
}

void die(const std::string msg) {
    die(msg, 1);
}
