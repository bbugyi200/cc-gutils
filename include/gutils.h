#ifndef INCLUDED_GUTILS
#define INCLUDED_GUTILS

/**************
*  Includes  *
**************/
#include <algorithm>
#include <fstream>
#include <glib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

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
    
/* Indicates which debugging mode (if any) is enabled. */
extern bool debug;
extern bool verbose;

/* Creates directory if it doesn't already exist. */
void create_dir(string const);

/* Returns XDG user directory. */
string get_xdg_dir(string const, string const);

/* Returns XDG user directory. Creates the directory if it does not exist. */
string init_xdg_dir(string const, string const);

/* Predicate that checks if directory exists. */
bool path_exists(string const);

/* Reads file contents into a string. */
string read_file(string const);

/* Enables debug mode if flag is 'true'. */
void set_debug_mode(bool, bool);

// convert string to uppercase
string toupper(string const);

}  // namespace gutils

/***********************
*  Logging Utilities  *
***********************/
#define IMSG(...) Logger::log("info", __VA_ARGS__)
#define DMSG(...) if (gutils::debug) { Logger::log("debug", __VA_ARGS__); }
#define DVMSG(...) \
    if (gutils::debug && gutils::verbose) { \
        Logger::log("vdebug", __VA_ARGS__); \
    }
#define DVAR(x) DVMSG(#x ": ", (x))
#define EMSG(...) Logger::log("error", __VA_ARGS__)

/*  Prints Logging Message
 *
 * Do not interface with this class directly. Use the `*MSG` macros.
 * */
class Logger {
    private:
        template<class T>
        static void _log(T&& x) {
            std::cout << x << std::endl;
        }

        template<class T, class... V>
        static void _log(T&& x, V&&... vargs) {
            std::cout << x;
            _log(vargs...);
        }

    public:
        template<class... V>
        static void log(string const mode, V&&... vargs) {
            std::cout << "[" + gutils::toupper(mode) + "] ";
            _log(vargs...);
        }
};

/***********************************
*  N-ary Tuples as Return Values  *
***********************************/
#define Unpack(x, y, fcall) \
    auto TT = fcall; \
    auto x = TT.first; \
    auto y = TT.second; \

template<class S = nullptr_t, class T = nullptr_t>
class TwoTuple {
    public:
        S first;
        T second;

        TwoTuple() : first(nullptr), second(nullptr) {};
        TwoTuple(S s, T t) : first(s), second(t) {};
};

#endif /* INCLUDED_GUTILS */
