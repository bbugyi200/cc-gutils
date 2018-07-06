#include "test.h"

static bool dir_exists(const char*);
static void test_xdg_userdir(const char*, const char*);
static std::string get_xdg_expected(const char*);
static std::string get_xdg_runtime_expected();

static const char *dirname = "/tmp/gutils_test_dir";
static const char *project_name = "TEST";

/****************
*  create_dir  *
****************/

class create_dir : public ::testing::Test {
    protected:
        void SetUp() {
            rmdir(dirname);
        }
};

TEST_F(create_dir, 1)
{
    EXPECT_FALSE(dir_exists(dirname));
    gutils::create_dir(dirname);
    EXPECT_TRUE(dir_exists(dirname));
}

static bool
dir_exists(const char *dirname) {
    struct stat sb;
    return stat(dirname, &sb) == 0 && S_ISDIR(sb.st_mode);
}

/*****************
*  get_xdg_dir  *
*****************/
TEST(get_xdg_dir, config)
{
    test_xdg_userdir("config", ".config");
}

TEST(get_xdg_dir, data)
{
    test_xdg_userdir("data", ".local/share");
}

static void
test_xdg_userdir(const char *dirtype, const char *local_path) {
    std::string expected = get_xdg_expected(local_path);
    std::string actual = gutils::get_xdg_dir(project_name, dirtype);

    EXPECT_EQ(expected, actual);
}

static std::string
get_xdg_expected(const char *local_path) {
    const char *user = getenv("USER");

    std::string expected = "/home/";
    expected.append(user);
    expected.append("/");
    expected.append(local_path);
    expected.append("/");
    expected.append(project_name);

    return expected;
}

TEST(get_xdg_dir, runtime)
{
    std::string actual = gutils::get_xdg_dir(project_name, "runtime");
    std::string expected = get_xdg_runtime_expected();

    EXPECT_EQ(expected, actual);
}

TEST(get_xdg_dir, init)
{
    gutils::init_xdg_dir(project_name, "runtime");
    std::string expected = get_xdg_runtime_expected();

    EXPECT_TRUE(dir_exists(expected.c_str()));
    rmdir(expected.c_str());
}

static std::string
get_xdg_runtime_expected() {
    std::string expected = "/run/user/1000/";
    expected.append(project_name);
    return expected;
}
