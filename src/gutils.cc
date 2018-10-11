#include <sys/types.h>
#include <sys/stat.h>

#include <gutils.h>

/**********************
*  Static Functions  *
**********************/
static string get_xdg_user_dir(char const *envvar, string const local_path,
                               string const project_name) {
    char const *user = getenv("USER");
    char const *xdg_env_value = getenv(envvar);

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

bool debug = false;
bool verbose = false;


void set_debug_mode(bool debug_flag, bool verbose_flag) {
    debug = debug_flag;
    verbose = verbose_flag;
    DMSG("Debug mode has been enabled.");
    DVMSG("Verbose output has been enabled.");
}

void create_dir(string const dirname) {
    if (!path_exists(dirname)) {
        mkdir(dirname.c_str(), 0700);
    }
}

string toupper(string const s) {
    string S = s;
    std::transform(S.begin(), S.end(), S.begin(), ::toupper);
    return S;
}

bool path_exists(string const dirname) {
    struct stat st = {0};
    return stat(dirname.c_str(), &st) != -1;
}

string read_file(string const filename) {
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

string init_xdg_dir(string const project_name, string const dirtype) {
    string dirname = get_xdg_dir(project_name, dirtype);
    create_dir(dirname);
    return dirname;
}

string get_xdg_dir(string const project_name, string const dirtype) {
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
