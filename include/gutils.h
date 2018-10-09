#ifndef INCLUDED_GUTILS
#define INCLUDED_GUTILS

/**************
*  Includes  *
**************/
#include <iostream>
#include <string>
#include <unistd.h>

/************
*  Macros  *
************/
#define dmsg(x) \
    if (gutils::debugging_enabled) { \
        std::cout << "[DEBUG] " << x << std::endl; \
    }

#define dvmsg(x) dmsg(#x ": " << (x))

/************************
*  Using Declarations  *
************************/
using std::string;

/********************
*  Global Namespace *
*********************/
void die(const string, int);
void die(const string);

/**********************
*  gutils Namespace  *
**********************/
namespace gutils {
    
// Indicates whether or not debugging mode is enabled.
extern bool debugging_enabled;

// Enables debug mode if flag is 'true'.
void set_debug_mode(bool);

// Creates directory if it doesn't already exist.
void create_dir(const string);

// Predicate that checks if directory exists.
bool path_exists(const string);

// Returns XDG user directory. Creates the directory if it does not exist.
string init_xdg_dir(const string, const string);

// Returns XDG user directory.
string get_xdg_dir(const string, const string);

}  // namespace gutils

#endif /* INCLUDED_GUTILS */
