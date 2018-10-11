#include <gutils.h>

void die(string const msg, int ec) {
    EMSG(msg);
    exit(ec);
}

void die(string const msg) {
    die(msg, 1);
}
