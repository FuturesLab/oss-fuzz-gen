#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

extern "C" {
    // Include the necessary header for lou_listTables
    #include <liblouis/liblouis.h>
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Call the function-under-test
    char **tables = lou_listTables();

    // Check if tables is not NULL
    if (tables != NULL) {
        // Iterate through the list of tables and print them
        for (int i = 0; tables[i] != NULL; ++i) {
            printf("Table: %s\n", tables[i]);
        }
    }

    return 0;
}