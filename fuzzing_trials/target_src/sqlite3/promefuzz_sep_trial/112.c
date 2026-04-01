// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_create_filename at sqlite3.c:175819:24 in sqlite3.h
// sqlite3_free_filename at sqlite3.c:175855:17 in sqlite3.h
// sqlite3_filename_journal at sqlite3.c:175932:24 in sqlite3.h
// sqlite3_filename_database at sqlite3.c:175928:24 in sqlite3.h
// sqlite3_filename_wal at sqlite3.c:175942:24 in sqlite3.h
// sqlite3_uri_parameter at sqlite3.c:175873:24 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

// Helper function to create a dummy file with given data
static void create_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

// Helper function to create a valid sqlite3_filename using sqlite3_create_filename
static sqlite3_filename create_valid_filename(const uint8_t *Data, size_t Size) {
    const char *params[] = {"key1", "value1", "key2", "value2"};
    // Ensure Data is null-terminated
    char *database = (char *)malloc(Size + 1);
    if (!database) return NULL;
    memcpy(database, Data, Size);
    database[Size] = '\0';

    sqlite3_filename filename = sqlite3_create_filename(database, "", "", 2, params);
    free(database);
    return filename;
}

// Helper function to clean up filename
static void cleanup_filename(sqlite3_filename filename) {
    sqlite3_free_filename(filename);
}

// Fuzzer entry point
int LLVMFuzzerTestOneInput_112(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare environment
    create_dummy_file(Data, Size);

    // Create a valid filename
    sqlite3_filename filename = create_valid_filename(Data, Size);
    if (!filename) return 0;

    // Fuzz sqlite3_filename_journal
    const char *journal = sqlite3_filename_journal(filename);
    if (journal) {
        // Handle journal filename
    }

    // Fuzz sqlite3_filename_database
    const char *database = sqlite3_filename_database(filename);
    if (database) {
        // Handle database filename
    }

    // Fuzz sqlite3_filename_wal
    const char *wal = sqlite3_filename_wal(filename);
    if (wal) {
        // Handle WAL filename
    }

    // Fuzz sqlite3_uri_parameter
    const char *paramValue = sqlite3_uri_parameter(filename, "key1");
    if (paramValue) {
        // Handle parameter value
    }

    // Cleanup
    cleanup_filename(filename);

    return 0;
}