#include <sys/types.h>
#include <sys/stat.h>

#include <gutils.h>

/**********************
*  Static Functions  *
**********************/
static string get_xdg_user_dir(const char *envvar, const string local_path,
                               const string project_name) {
    const char *user = getenv("USER");
    const char *xdg_env_value = getenv(envvar);

    string xdg_path = "";

    if (xdg_env_value) {
        xdg_path += xdg_env_value;
    } else {
        xdg_path += "/home/";
        xdg_path += user;
        xdg_path += "/";
        xdg_path += local_path;
    }

    xdg_path += "/";
    xdg_path += project_name;
    return xdg_path;
}

/**********************
*  gutils Namespace  *
**********************/
namespace gutils
{

bool debugging_enabled = false;


void set_debug_mode(bool debug_flag) {
    debugging_enabled = debug_flag;
    dmsg("Debug Mode Enabled");
}

void create_dir(const string dirname) {
    if (!path_exists(dirname)) {
        mkdir(dirname.c_str(), 0700);
    }
}

bool path_exists(const string dirname) {
    struct stat st = {0};
    return stat(dirname.c_str(), &st) != -1;
}

string init_xdg_dir(const string project_name, const string dirtype) {
    auto dirname = get_xdg_dir(project_name, dirtype);
    create_dir(dirname);
    return dirname;
}

string get_xdg_dir(const string project_name, const string dirtype) {
    if (dirtype == "config") {
        return get_xdg_user_dir("XDG_CONFIG_HOME", ".config", project_name);
    } else if (dirtype == "data") {
        return get_xdg_user_dir("XDG_DATA_HOME", ".local/share", project_name);
    } else if (dirtype == "runtime") {
        string xdg_path = "/run/user/1000/";
        xdg_path += project_name;
        return xdg_path;
    } else {
        throw "Parameter @dirtype must be in ['config', 'data', 'runtime'].";
    }
}

}  // namespace gutils
