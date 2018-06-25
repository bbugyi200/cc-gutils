#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "gutils.h"

/** Creates directory if it doesn't already exist. **/
void gutils::create_dir(const char *dirname) {
    struct stat st = {0};
    if (stat(dirname, &st) == -1) {
        mkdir(dirname, 0700);
    }
}

static std::string get_xdg_user_dir(const char *envvar, const std::string local_path,
                                    const std::string project_name) {
    const char *user = getenv("USER");
    const char *xdg_env_value = getenv(envvar);

    std::string xdg_path = "";

    if (xdg_env_value == NULL) {
        xdg_path.append("/home/");
        xdg_path.append(user);
        xdg_path.append("/");
        xdg_path.append(local_path);
    } else {
        xdg_path.append(xdg_env_value);
    }

    xdg_path.append("/");
    xdg_path.append(project_name);
    return xdg_path;
}

std::string gutils::get_xdg_dir(const std::string project_name, const std::string dirtype) {
    if (dirtype == "config") {
        return get_xdg_user_dir("XDG_CONFIG_HOME", ".config", project_name);
    } else if (dirtype == "data") {
        return get_xdg_user_dir("XDG_DATA_HOME", ".local/share", project_name);
    } else if (dirtype == "runtime") {
        std::string xdg_path = "/run/user/1000/";
        xdg_path.append(project_name);
        return xdg_path;
    } else {
        throw "Parameter @dirtype must be in ['config', 'data', 'runtime'].";
    }
}
