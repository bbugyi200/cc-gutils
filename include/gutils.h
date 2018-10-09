#ifndef INCLUDED_GUTILS
#define INCLUDED_GUTILS 1

#include <iostream>
#include <string>
#include <unistd.h>

#define dmsg(x) \
    if (debugging_enabled()) { \
        std::cout << "[DEBUG] " << x << std::endl; \
    }

#define dvmsg(x) dmsg(#x ": " << (x))

void die(const std::string, int);
void die(const std::string);
bool debugging_enabled(bool);
bool debugging_enabled();
void set_debug_mode(bool);

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
