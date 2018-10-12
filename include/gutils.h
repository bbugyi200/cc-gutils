/** @file gutils.h */

/**  @mainpage gutils Library
 *
 * Global C++ utility library that I use in several of my other projects. All relevant
 * documentation can be found in the gutils.h header.
 * */

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
    
extern bool debug;  /**< Debug Flag */
extern bool verbose;  /**< Verbose Flag */

bool path_exists(string const);
string get_xdg_dir(string const, string const);
string init_xdg_dir(string const, string const);
string read_file(string const);
string toupper(string const);
void create_dir(string const);
void set_debug_mode(bool, bool);

}  // namespace gutils

/***********************
*  Logging Utilities  *
***********************/
#define IMSG(...) Logger::log("info", __VA_ARGS__)  /**< INFO Logging Message */
#define EMSG(...) Logger::log("error", __VA_ARGS__)  /**< ERROR Logging Message */
#define DMSG(...) if (gutils::debug) { Logger::log("debug", __VA_ARGS__); }  /**< DEBUG Logging Message */

/** VDEBUG Logging Message */
#define DVMSG(...) \
    if (gutils::debug && gutils::verbose) { \
        Logger::log("vdebug", __VA_ARGS__); \
    }

#define DVAR(x) DVMSG(#x " => ", (x))  /**< Evaluate Variables Value (VDEBUG) */

/**  Prints Logging Message
 *
 * Do not interface with this class directly. Use the `*MSG` macros instead (#IMSG, #EMSG, #DMSG, etc.).
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
/** Unpacks TwoTuple Object */
#define Unpack(a, b, fcall) \
    auto TT = fcall; \
    auto a = TT.a; \
    auto b = TT.b; \

/**  Used to Return Two Values from a Function
 *
 * Use the #Unpack macro to unpack these values from function call results.
 * */
template<class S = nullptr_t, class T = nullptr_t>
class TwoTuple {
    public:
        S a;
        T b;

        TwoTuple() : a(nullptr), b(nullptr) {};
        TwoTuple(S s, T t) : a(s), b(t) {};
};

#endif /* INCLUDED_GUTILS */
