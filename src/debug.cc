#include <gutils.h>

bool debugging_enabled(bool debug_flag) {
    static bool is_enabled;
    if (!debug_flag) {
        return is_enabled;
    } else {
        is_enabled = debug_flag;
        return is_enabled;
    }
}

bool debugging_enabled() {
    return debugging_enabled(false);
}

void set_debug_mode(bool debug_flag) {
    debugging_enabled(debug_flag);
    dmsg("Debug Mode Enabled");
}
