// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_setLogLevel at logging.c:143:1 in liblouis.h
// lou_indexTables at metadata.c:945:1 in liblouis.h
// lou_findTable at metadata.c:1063:1 in liblouis.h
// lou_findTables at metadata.c:1110:1 in liblouis.h
// lou_free at compileTranslationTable.c:5363:1 in liblouis.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "liblouis.h"

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Set log level using the first byte of data
    logLevels level = static_cast<logLevels>(Data[0]);
    lou_setLogLevel(level);

    // Prepare dummy table names
    const char *tables[] = {"table1", "table2", nullptr};
    lou_indexTables(tables);

    // Extract a query string from the input data
    size_t querySize = Size - 1;
    char *query = static_cast<char *>(malloc(querySize + 1));
    if (!query) {
        return 0;
    }
    memcpy(query, Data + 1, querySize);
    query[querySize] = '\0';

    // Find a single table
    char *foundTable = lou_findTable(query);
    if (foundTable) {
        free(foundTable);
    }

    // Find multiple tables
    char **foundTables = lou_findTables(query);
    if (foundTables) {
        for (char **table = foundTables; *table; ++table) {
            free(*table);
        }
        free(foundTables);
    }

    // Clean up
    free(query);
    lou_free();

    return 0;
}