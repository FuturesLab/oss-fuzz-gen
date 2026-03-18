// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_db_readonly at sqlite3.c:175999:16 in sqlite3.h
// sqlite3_filename_wal at sqlite3.c:175942:24 in sqlite3.h
// sqlite3_wal_checkpoint_v2 at sqlite3.c:173557:16 in sqlite3.h
// sqlite3_set_errmsg at sqlite3.c:173751:16 in sqlite3.h
// sqlite3_wal_checkpoint at sqlite3.c:173627:16 in sqlite3.h
// sqlite3_uri_parameter at sqlite3.c:175873:24 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Helper function to create a dummy SQLite database
static sqlite3* create_dummy_db() {
    sqlite3 *db = NULL;
    int rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) {
        if (db) sqlite3_close(db);
        return NULL;
    }
    return db;
}

// Helper function to create a dummy file
static void create_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("Dummy content", file);
        fclose(file);
    }
}

// Helper function to extract a string from the input data
static const char* extract_string(const uint8_t *Data, size_t Size, size_t *offset) {
    if (*offset >= Size) return NULL;
    const char *str = (const char *)&Data[*offset];
    size_t str_len = strnlen(str, Size - *offset);
    if (*offset + str_len >= Size) return NULL; // Ensure null-terminator is within bounds
    *offset += str_len + 1;
    return str;
}

int LLVMFuzzerTestOneInput_115(const uint8_t *Data, size_t Size) {
    create_dummy_file();

    sqlite3 *db = create_dummy_db();
    if (!db) return 0;

    size_t offset = 0;
    const char *zDbName = extract_string(Data, Size, &offset);
    const char *zParam = extract_string(Data, Size, &offset);
    const char *zErrMsg = extract_string(Data, Size, &offset);

    // Test sqlite3_db_readonly
    if (zDbName) {
        int readonly = sqlite3_db_readonly(db, zDbName);
    }

    // Test sqlite3_filename_wal
    if (zDbName && strlen(zDbName) > 0) {
        const char *wal_filename = sqlite3_filename_wal(zDbName);
        // Ensure that wal_filename is not NULL before accessing it
        if (wal_filename) {
            // Use wal_filename for any further operations if needed
        }
    }

    // Test sqlite3_wal_checkpoint_v2
    int pnLog, pnCkpt;
    int checkpoint_mode = SQLITE_CHECKPOINT_PASSIVE;
    if (offset < Size) {
        checkpoint_mode = Data[offset] % 5; // Randomly select a mode
        offset++;
    }
    int rc = sqlite3_wal_checkpoint_v2(db, zDbName, checkpoint_mode, &pnLog, &pnCkpt);

    // Test sqlite3_set_errmsg
    if (zErrMsg) {
        sqlite3_set_errmsg(db, rc, zErrMsg);
    }

    // Test sqlite3_wal_checkpoint
    rc = sqlite3_wal_checkpoint(db, zDbName);

    // Test sqlite3_uri_parameter
    if (zParam) {
        const char *param_value = sqlite3_uri_parameter(zDbName, zParam);
    }

    sqlite3_close(db);
    return 0;
}