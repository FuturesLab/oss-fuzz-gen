// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_result_null at sqlite3.c:78859:17 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_enable_load_extension at sqlite3.c:127686:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_load_extension at sqlite3.c:127655:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_set_authorizer at sqlite3.c:110840:16 in sqlite3.h
// sqlite3_create_function at sqlite3.c:173127:16 in sqlite3.h
// sqlite3_db_name at sqlite3.c:175965:24 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int dummy_authorizer(void *pUserData, int action, const char *arg1, const char *arg2, const char *arg3, const char *arg4) {
    return SQLITE_OK;
}

static void dummy_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    sqlite3_result_null(context);
}

int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    int rc;

    // Open a database connection
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Enable load extension
    rc = sqlite3_enable_load_extension(db, 1);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Fuzz sqlite3_load_extension
    char fileName[256];
    snprintf(fileName, sizeof(fileName), "./dummy_file_%zu", Size);
    FILE *file = fopen(fileName, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
    rc = sqlite3_load_extension(db, fileName, NULL, &errMsg);
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Fuzz sqlite3_set_authorizer
    rc = sqlite3_set_authorizer(db, dummy_authorizer, NULL);

    // Fuzz sqlite3_create_function
    rc = sqlite3_create_function(db, "dummy_func", 1, SQLITE_UTF8, NULL, dummy_function, NULL, NULL);

    // Fuzz sqlite3_db_name
    const char *dbName = sqlite3_db_name(db, 0);

    // Clean up
    sqlite3_close(db);
    remove(fileName);

    return 0;
}