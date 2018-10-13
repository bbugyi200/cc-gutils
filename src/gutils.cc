#include <sys/types.h>
#include <sys/stat.h>

#include <gutils.h>

static std::string get_xdg_user_dir(char const *envvar, std::string const &local_path,
                               std::string const &project_name) {
    char const *user = getenv("USER");
    char const *xdg_env_value = getenv(envvar);

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


namespace gutils
{

void die(std::string const &msg, int ec) {
    EMSG(msg);
    exit(ec);
}

std::string toupper(std::string const &s) {
    std::string S = s;
    std::transform(S.begin(), S.end(), S.begin(), ::toupper);
    return S;
}

namespace logging
{

LogLevel log_level = INFO;

void set_log_level(bool debug_flag, bool verbose_flag) {
    log_level = debug_flag && verbose_flag ? VDEBUG
                : debug_flag               ? DEBUG
                : INFO;

    DMSG("Debug mode has been enabled.");
    DVMSG("Verbose output has been enabled.");
}

}  // namespace logging

namespace path
{

void create_dir(std::string const &dirname) {
    if (!exists(dirname)) {
        mkdir(dirname.c_str(), 0700);
    }
}

bool exists(std::string const &dirname) {
    struct stat st = {0};
    return stat(dirname.c_str(), &st) != -1;
}

std::string read_file(std::string const &filename) {
    char *out;
    GError *e = nullptr;
    GIOChannel *f = g_io_channel_new_file(filename.c_str(), "r", &e);

    if (!f) {
        die("Failed to open file " + filename + ".");
    }

    if (g_io_channel_read_to_end(f, &out, nullptr, &e) != G_IO_STATUS_NORMAL) {
        die("Unable to read file " + filename + ".");
    }

    return out;
}

std::string init_xdg_dir(std::string const &project_name, std::string const &dirtype) {
    std::string dirname = get_xdg_dir(project_name, dirtype);
    create_dir(dirname);
    return dirname;
}

std::string get_xdg_dir(std::string const &project_name, std::string const &dirtype) {
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

}  // namespace path

}  // namespace gutils
