 #ifndef INCLUDED_GUTILS
#define INCLUDED_GUTILS

#include <string>

/** Global Utilities **/
namespace gutils {
    void create_dir(const std::string);
    void create_dir(const char*);

    std::string init_xdg_dir(const std::string, const std::string);
    std::string get_xdg_dir(const std::string, const std::string);
}

#endif /* INCLUDED_GUTILS */
