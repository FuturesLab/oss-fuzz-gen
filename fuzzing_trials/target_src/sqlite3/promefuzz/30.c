// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int64 at sqlite3.c:80118:16 in sqlite3.h
// sqlite3_bind_double at sqlite3.c:80104:16 in sqlite3.h
// sqlite3_bind_text64 at sqlite3.c:80167:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
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

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Write input data to a dummy file
    write_dummy_file(Data, Size);

    // Open a database connection
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a dummy SQL statement
    const char *sql = "CREATE TABLE dummy (id INTEGER, value TEXT); INSERT INTO dummy (id, value) VALUES (?, ?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Safely extract values from the input data
    int int_value = Size > 0 ? Data[0] : 0;
    sqlite3_int64 int64_value = 0;
    if (Size >= sizeof(sqlite3_int64)) {
        memcpy(&int64_value, Data, sizeof(sqlite3_int64));
    }
    double double_value = 0.0;
    if (Size >= sizeof(sqlite3_int64) + sizeof(double)) {
        memcpy(&double_value, Data + sizeof(sqlite3_int64), sizeof(double));
    }
    const char *text_value = Size > sizeof(sqlite3_int64) + sizeof(double) ? (const char *)(Data + sizeof(sqlite3_int64) + sizeof(double)) : "";
    sqlite3_uint64 text_length = strlen(text_value);
    unsigned char encoding = SQLITE_UTF8;

    // Bind integer value
    sqlite3_bind_int(stmt, 1, int_value);

    // Bind int64 value
    sqlite3_bind_int64(stmt, 1, int64_value);

    // Bind double value
    sqlite3_bind_double(stmt, 1, double_value);

    // Bind text value
    sqlite3_bind_text64(stmt, 2, text_value, text_length, SQLITE_STATIC, encoding);

    // Bind integer value again
    sqlite3_bind_int(stmt, 1, int_value);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}