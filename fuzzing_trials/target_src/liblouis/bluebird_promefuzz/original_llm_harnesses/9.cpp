// This fuzz driver is generated for library liblouis, aiming to fuzz the following functions:
// lou_listTables at metadata.c:1172:1 in liblouis.h
// lou_getTableInfo at metadata.c:1142:1 in liblouis.h
// lou_freeTableInfo at metadata.c:1167:1 in liblouis.h
// lou_freeTableFiles at compileTranslationTable.c:4933:1 in liblouis.h
// lou_freeEmphClasses at compileTranslationTable.c:5095:1 in liblouis.h
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

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    // Step 1: Prepare the environment
    char **tableList = lou_listTables();
    if (tableList != nullptr) {
        // Fuzzing lou_getTableInfo with table names and fuzzed data as key
        for (size_t i = 0; tableList[i] != nullptr; ++i) {
            char *info = lou_getTableInfo(tableList[i], reinterpret_cast<const char*>(Data));
            if (info != nullptr) {
                lou_freeTableInfo(info);
            }
        }

        // Step 2: Cleanup
        lou_freeTableFiles(tableList);
    }

    // Fuzzing lou_freeEmphClasses with fuzzed data
    char *dummyData = static_cast<char*>(malloc(Size + 1));
    if (dummyData) {
        memcpy(dummyData, Data, Size);
        dummyData[Size] = '\0'; // Null-terminate to ensure it can be used as a string

        char const **emphClasses = static_cast<char const **>(malloc(2 * sizeof(char*)));
        if (emphClasses) {
            emphClasses[0] = dummyData;
            emphClasses[1] = nullptr;
            lou_freeEmphClasses(emphClasses);
            // No need to manually free emphClasses, as lou_freeEmphClasses handles it
        } else {
            free(dummyData); // Free dummyData if emphClasses allocation fails
        }
    }

    return 0;
}