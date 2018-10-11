#ifndef INCLUDED_GUTILS
#define INCLUDED_GUTILS

/**************
*  Includes  *
**************/
#include <fstream>
#include <glib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
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
    
/* Indicates which debugging mode (if any) is enabled. */
extern bool debug;
extern bool verbose;

/* Enables debug mode if flag is 'true'. */
void set_debug_mode(bool, bool);

/* Creates directory if it doesn't already exist. */
void create_dir(string const);

/* Predicate that checks if directory exists. */
bool path_exists(string const);

/* Reads file contents into a string. */
string read_file(string const);

/* Returns XDG user directory. Creates the directory if it does not exist. */
string init_xdg_dir(string const, string const);

/* Returns XDG user directory. */
string get_xdg_dir(string const, string const);

}  // namespace gutils

/*******************
*  Debug Helpers  *
*******************/
#define DMSG(...) DebugPrint::debug_print("DEBUG", __VA_ARGS__)
#define DVMSG(...) if (gutils::verbose) { DebugPrint::debug_print("VDEBUG", __VA_ARGS__); }
#define DVAR(x) DVMSG(#x ": ", (x))

/*  Prints Message iff Debug Mode is Enabled
 *
 * Do not interface with this class directly. Use the `DMSG` macro.
 * */
class DebugPrint {
    private:
        template<class T>
        static void _debug_print(T&& x) {
            std::cout << x << std::endl;
        }

        template<class T, class... V>
        static void _debug_print(T&& x, V&&... vargs) {
            std::cout << x;
            _debug_print(vargs...);
        }

    public:
        template<class... V>
        static void debug_print(string const mode, V&&... vargs) {
            if (gutils::debug) {
                std::cout << "[" + mode + "] ";
                _debug_print(vargs...);
            }
        }
};

/***********************************
*  N-ary Tuples as Return Values  *
***********************************/
#define Unpack(x, y, fcall) \
    auto TT = fcall; \
    auto x = TT.first; \
    auto y = TT.second; \

template<class S, class T>
class TwoTuple {
    public:
        S first;
        T second;

        TwoTuple(S s, T t) : first(s), second(t) {};
};

#endif /* INCLUDED_GUTILS */
