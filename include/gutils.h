#ifndef INCLUDED_GUTILS
#define INCLUDED_GUTILS

/**************
*  Includes  *
**************/
#include <glib.h>
#include <iostream>
#include <string>
#include <unistd.h>

/************************
*  Using Declarations  *
************************/
using std::string;

/********************
*  Global Namespace *
*********************/
void die(string const, int);
void die(string const);

/**********************
*  gutils Namespace  *
**********************/
namespace gutils {
    
// Indicates whether or not debugging mode is enabled.
extern bool debugging_enabled;

// Enables debug mode if flag is 'true'.
void set_debug_mode(bool);

// Creates directory if it doesn't already exist.
void create_dir(string const);

// Predicate that checks if directory exists.
bool path_exists(string const);

// Reads entire file contents into a string.
string read_file(string const);

// Returns XDG user directory. Creates the directory if it does not exist.
string init_xdg_dir(string const, string const);

// Returns XDG user directory.
string get_xdg_dir(string const, string const);

}  // namespace gutils

/*******************
*  Debug Helpers  *
*******************/
#define dvmsg(x) dmsg(#x ": ", (x))

template<class T>
void debug_print(T&& x) {
    std::cout << x << std::endl;
}

template<class T, class... V>
void debug_print(T&& x, V&&... vargs) {
    std::cout << x;
    debug_print(vargs...);
}

template<class... V>
void dmsg(V&&... vargs) {
    if (gutils::debugging_enabled) {
        std::cout << "[DEBUG] ";
        debug_print(vargs...);
    }
}

#endif /* INCLUDED_GUTILS */
