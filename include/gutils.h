 #ifndef INCLUDED_GUTILS
#define INCLUDED_GUTILS

#include <string>

/** Global Utilities **/
namespace gutils {
    /** Creates directory if it doesn't already exist. **/
    void create_dir(const std::string);
    void create_dir(const char*);

    /** Returns XDG user directory. Creates the directory if it does not exist. **/
    std::string init_xdg_dir(const std::string, const std::string);

    /** Returns XDG user directory. **/
    std::string get_xdg_dir(const std::string, const std::string);
}

#endif /* INCLUDED_GUTILS */
