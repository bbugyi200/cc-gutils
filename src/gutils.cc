#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <gutils.h>

static std::string get_xdg_user_dir(const char*, const std::string, const std::string);

void 
gutils::create_dir(const char *dirname) {
    struct stat st = {0};
    if (stat(dirname, &st) == -1) {
        mkdir(dirname, 0700);
    }
}

void
gutils::create_dir(const std::string dirname) {
    return create_dir(dirname.c_str());
}


std::string
gutils::init_xdg_dir(const std::string project_name, const std::string dirtype) {
    auto dirname = get_xdg_dir(project_name, dirtype);
    create_dir(dirname);
    return dirname;
}

std::string
gutils::get_xdg_dir(const std::string project_name, const std::string dirtype) {
    if (dirtype == "config") {
        return get_xdg_user_dir("XDG_CONFIG_HOME", ".config", project_name);
    } else if (dirtype == "data") {
        return get_xdg_user_dir("XDG_DATA_HOME", ".local/share", project_name);
    } else if (dirtype == "runtime") {
        std::string xdg_path = "/run/user/1000/";
        xdg_path += project_name;
        return xdg_path;
    } else {
        throw "Parameter @dirtype must be in ['config', 'data', 'runtime'].";
    }
}

static std::string
get_xdg_user_dir(const char *envvar, const std::string local_path,
                                    const std::string project_name) {
    const char *user = getenv("USER");
    const char *xdg_env_value = getenv(envvar);

    std::string xdg_path = "";

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
