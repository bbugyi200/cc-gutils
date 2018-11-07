/** @file gutils.h */

/**  @mainpage gutils Library
 *
 * Global C++ utility library that I use in several of my other projects. All relevant
 * documentation can be found in the gutils.h header.
 * */

#ifndef INCLUDED_GUTILS
#define INCLUDED_GUTILS

/**********************
*  Included Headers  *
**********************/
#include <algorithm>
#include <fstream>
#include <glib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

/**********************
*  gutils Namespace  *
**********************/
/** Namespace for gutils library. */
namespace gutils {

/**  Used to Return Two Values from a Function.
 *
 * Use the #UNPACK macro to unpack these values from function call results.
 * */
template<class S = nullptr_t, class T = nullptr_t>
class TwoTuple {
    public:
        S a;
        T b;

        TwoTuple() : a(nullptr), b(nullptr) {};
        TwoTuple(S s, T t) : a(s), b(t) {};
};

/**  Exit script after printing error message to screen.
 *
 * @param msg Error Message.
 * @param ec Exit Code.
 * */
void die(std::string const &msg, int ec = 1);

/**
 * @param s String to make uppercase.
 * @return Uppercase string.
 * */
std::string toupper(std::string const &s);

/** Global Filesystem Utilities */
namespace path
{

/**
 * @param filename File to read.
 * @return File contents.
 * */
std::string read_file(std::string const &filename);

/** Creates directory if it does not already exist.
 *
 * @param dirname The directory to create.
 */
void create_dir(std::string const &dirname);

/**  Checks if the given directory exists.
 *
 * @param dirname Directory name.
 * @return TRUE if directory exists. FALSE otherwise.
 * */
bool exists(std::string const &dirname);

/**
 * @param project_name Name of the program that will use this directory.
 * @param dirtype XDG Directory Type (config | data | runtime).
 * @return XDG User Directory
 * */
std::string get_xdg_dir(std::string const &project_name, std::string const &dirtype);

/** Wrapper for ::get_xdg_dir.
 *
 * @sideeffects
 * @li Creates the XDG directory if it does not already exist.
 * */
std::string init_xdg_dir(std::string const&, std::string const&);

}  // namespace path

/** Global Logging Utilities */
namespace logging
{

enum LogLevel { INFO, DEBUG, VDEBUG };  /**< Available Log Levels */

extern LogLevel log_level;  /**< Global Logging Level */

/**  Prints Logging Messages.
 *
 * Do not interface with this class directly. Use the `*MSG` macros instead
 * (#IMSG, #EMSG, #DMSG, etc.).
 * */
class Logger {
    private:
        template<class T>
        static void print_values(T&& x) {
            std::cout << x << std::endl;
        }

        template<class T, class... V>
        static void print_values(T&& x, V&&... vargs) {
            std::cout << x;
            print_values(vargs...);
        }

    public:
        template<class... V>
        static void log(std::string const &mode, V&&... vargs) {
            std::cout << "[" + gutils::toupper(mode) + "] ";
            print_values(vargs...);
        }
};

/**  Sets Logging Mode (INFO, DEBUG, or VDEBUG).
 *
 * Defaults to INFO if `@debug_flag` and `@verbose_flag` are both false.
 *
 * @sideeffects
 * @li Modifies ::log_level.
 *
 * @param debug_flag Enable debugging.
 * @param verbose_flag Enable verbose output.
 * */
void set_log_level(bool debug_flag, bool verbose_flag);

}  // namespace logging

}  // namespace gutils

/************************
*  Using Declarations  *
************************/
using std::string;
using gutils::die;

/************
*  Macros  *
************/
#define IMSG(...) gutils::logging::Logger::log("info", __VA_ARGS__)  /**< Send INFO Logging Message. */
#define EMSG(...) gutils::logging::Logger::log("error", __VA_ARGS__)  /**< Send ERROR Logging Message. */

/** Send DEBUG Logging Message. */
#define DMSG(...) \
    if (gutils::logging::log_level >= gutils::logging::DEBUG) { \
        gutils::logging::Logger::log("debug", __VA_ARGS__); \
    }

#define DVEVAL(x) DVMSG(#x " => ", (x))  /**< Evaluates Expression (VDEBUG). */

/** Send VDEBUG Logging Message. */
#define DVMSG(...) \
    if (gutils::logging::log_level >= gutils::logging::VDEBUG) { \
        gutils::logging::Logger::log("vdebug", __VA_ARGS__); \
    }

/** Unpacks TwoTuple Object. */
#define UNPACK(A, B, fcall) \
    auto TT = fcall; \
    auto A = TT.a; \
    auto B = TT.b; \

#endif /* INCLUDED_GUTILS */
