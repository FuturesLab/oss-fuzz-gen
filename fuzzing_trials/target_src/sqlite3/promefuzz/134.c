// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_initialize at sqlite3.c:171208:16 in sqlite3.h
// sqlite3_os_init at sqlite3.c:33768:16 in sqlite3.h
// sqlite3_global_recover at sqlite3.c:174934:16 in sqlite3.h
// sqlite3_os_end at sqlite3.c:33901:16 in sqlite3.h
// sqlite3_shutdown at sqlite3.c:171390:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void handle_sqlite3_config(int config_option) {
    // Attempt a few common configurations for fuzzing
    int rc;
    switch (config_option) {
        case SQLITE_CONFIG_SINGLETHREAD:
        case SQLITE_CONFIG_MULTITHREAD:
        case SQLITE_CONFIG_SERIALIZED:
            rc = sqlite3_config(config_option);
            break;
        default:
            rc = SQLITE_MISUSE;
            break;
    }
    if (rc != SQLITE_OK && rc != SQLITE_MISUSE) {
        fprintf(stderr, "sqlite3_config error: %d\n", rc);
    }
}

int LLVMFuzzerTestOneInput_134(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there is enough data

    // Initialize SQLite library
    int rc = sqlite3_initialize();
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_initialize error: %d\n", rc);
        return 0;
    }

    // Extract an integer from the input data to use as a configuration option
    int config_option = *(int*)Data;

    // Fuzz sqlite3_config with the extracted option
    handle_sqlite3_config(config_option);

    // Call other functions
    rc = sqlite3_os_init();
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_os_init error: %d\n", rc);
    }

    rc = sqlite3_global_recover();
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_global_recover error: %d\n", rc);
    }

    rc = sqlite3_os_end();
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_os_end error: %d\n", rc);
    }

    rc = sqlite3_shutdown();
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_shutdown error: %d\n", rc);
    }

    return 0;
}