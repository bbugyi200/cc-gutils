#include "test.h"

static const char *dirname = "/tmp/gutils_test_dir";
TEST_GROUP(create_dir)
{
    void setup() {
        rmdir(dirname);
    }
};

static bool dir_exists(const char *dirname) {
    struct stat sb;
    return stat(dirname, &sb) == 0 && S_ISDIR(sb.st_mode);
}

TEST(create_dir, 1)
{
    CHECK_FALSE(dir_exists(dirname));
    gutils::create_dir(dirname);
    CHECK_TRUE(dir_exists(dirname));
}

TEST_GROUP(get_xdg_dir)
{
};

static const char *project_name = "TEST";
void test_xdg_userdir(const char *dirtype, const char *partial_path) {
    const char *user = getenv("USER");

    std::string actual = gutils::get_xdg_dir(project_name, dirtype);

    std::string expected = "/home/";
    expected.append(user);
    expected.append("/");
    expected.append(partial_path);
    expected.append("/");
    expected.append(project_name);

    CHECK_EQUAL(expected, actual);
}

TEST(get_xdg_dir, userdirs)
{
    test_xdg_userdir("config", ".config");
    test_xdg_userdir("data", ".local/share");
}

TEST(get_xdg_dir, runtime)
{
    std::string actual = gutils::get_xdg_dir(project_name, "runtime");

    std::string expected = "/run/user/1000/";
    expected.append(project_name);

    CHECK_EQUAL(expected, actual);
}
