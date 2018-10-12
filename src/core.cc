/** @file core.cc */

#include <gutils.h>

/**  Exit script after printing error message to screen.
 *
 * @param msg Error Message
 * @param ec Exit Code (Default: 1)
 * */
void die(string const msg, int ec) {
    EMSG(msg);
    exit(ec);
}

void die(string const msg) {
    die(msg, 1);
}
