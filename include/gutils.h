#ifndef INCLUDED_GUTILS
#define INCLUDED_GUTILS

#include <iostream>
#include <string>
#include <unistd.h>

#define dmsg(x) \
    if (debugging_enabled) { \
        std::cout << "[DEBUG] " << x << std::endl; \
    }

#define dvmsg(x) dmsg(#x ": " << (x))

static bool debugging_enabled = false;

inline void set_debug_mode(bool debug_flag) {
    debugging_enabled = debug_flag;
    dmsg("Debug Mode Enabled");
}

inline void die(const std::string msg, int ec) {
    std::cout << msg << std::endl;
    exit(ec);
}

inline void die(const std::string msg) {
    die(msg, 1);
}

namespace gutils {

// Creates directory if it doesn't already exist.
void create_dir(const char*);
void create_dir(const std::string);

// Returns XDG user directory. Creates the directory if it does not exist.
std::string init_xdg_dir(const std::string, const std::string);

// Returns XDG user directory.
std::string get_xdg_dir(const std::string, const std::string);

}  // namespace gutils

#endif /* INCLUDED_GUTILS */
