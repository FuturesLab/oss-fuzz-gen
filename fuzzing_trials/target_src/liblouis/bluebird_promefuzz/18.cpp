#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include "../../liblouis/liblouis.h"

static void cleanup(char **array) {
    if (array) {
        for (int i = 0; array[i] != nullptr; ++i) {
            free(array[i]);
        }
        free(array);
    }
}

static char **dummyResolver(const char *table, const char *base) {
    return nullptr;
}

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    // Prepare a null-terminated string from the input data
    char *input = (char *)malloc(Size + 1);
    if (!input) return 0;
    memcpy(input, Data, Size);
    input[Size] = '\0';

    // Fuzz lou_listTables
    char **tableList = lou_listTables();
    cleanup(tableList);

    // Fuzz lou_getEmphClasses
    const char **emphClasses = lou_getEmphClasses(input);
    if (emphClasses) {
        for (int i = 0; emphClasses[i] != nullptr; ++i) {
            free((void *)emphClasses[i]);
        }
        free(emphClasses);
    }

    // Fuzz lou_indexTables
    const char *tables[] = { input, nullptr };
    lou_indexTables(tables);

    // Fuzz lou_getTable
    const void *table = lou_getTable(input);
    // Normally, you would do something with `table`, but since it's read-only, we skip it

    // Register dummy resolver function for lou_registerTableResolver
    lou_registerTableResolver(dummyResolver);

    // Fuzz lou_findTables
    char **foundTables = lou_findTables(input);
    cleanup(foundTables);

    free(input);
    return 0;
}