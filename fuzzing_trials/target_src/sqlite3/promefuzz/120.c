// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_result_null at sqlite3.c:78859:17 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_create_module at sqlite3.c:145696:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_create_function at sqlite3.c:173127:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_overload_function at sqlite3.c:173233:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_create_module_v2 at sqlite3.c:145711:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_declare_vtab at sqlite3.c:146399:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
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

static int dummy_xCreate(sqlite3 *db, void *pAux, int argc, const char *const *argv, sqlite3_vtab **ppVTab, char **pzErr) {
    return SQLITE_OK;
}

static int dummy_xConnect(sqlite3 *db, void *pAux, int argc, const char *const *argv, sqlite3_vtab **ppVTab, char **pzErr) {
    return SQLITE_OK;
}

static sqlite3_module dummy_module = {
    1, /* iVersion */
    dummy_xCreate,
    dummy_xConnect,
    0, /* xBestIndex */
    0, /* xDisconnect */
    0, /* xDestroy */
    0, /* xOpen */
    0, /* xClose */
    0, /* xFilter */
    0, /* xNext */
    0, /* xEof */
    0, /* xColumn */
    0, /* xRowid */
    0, /* xUpdate */
    0, /* xBegin */
    0, /* xSync */
    0, /* xCommit */
    0, /* xRollback */
    0, /* xFindFunction */
    0, /* xRename */
    0, /* xSavepoint */
    0, /* xRelease */
    0, /* xRollbackTo */
    0, /* xShadowName */
    0  /* xIntegrity */
};

static void dummy_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    sqlite3_result_null(context);
}

int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size) {
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Fuzzing sqlite3_create_module
    const char *moduleName = "dummy_module";
    rc = sqlite3_create_module(db, moduleName, &dummy_module, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Fuzzing sqlite3_create_function
    const char *functionName = "dummy_function";
    rc = sqlite3_create_function(db, functionName, 1, SQLITE_UTF8, NULL, dummy_function, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Fuzzing sqlite3_overload_function
    rc = sqlite3_overload_function(db, "overload_func", 2);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Fuzzing sqlite3_create_module_v2
    rc = sqlite3_create_module_v2(db, "dummy_module_v2", &dummy_module, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Fuzzing sqlite3_declare_vtab
    const char *createTableSQL = "CREATE TABLE x(a INT, b TEXT);";
    rc = sqlite3_declare_vtab(db, createTableSQL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_close(db);
    return 0;
}