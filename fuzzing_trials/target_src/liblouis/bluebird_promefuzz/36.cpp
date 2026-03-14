#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../../liblouis/liblouis.h"

static void customLogCallback(logLevels level, const char *message) {
    // Custom log callback that does nothing for now
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare a dummy file for lou_logFile
    FILE *dummyFile = fopen("./dummy_file", "w");
    if (dummyFile) fclose(dummyFile);

    // 1. Fuzz lou_logPrint
    lou_logPrint("Fuzzing lou_logPrint with input size: %zu\n", Size);

    // 2. Fuzz lou_registerLogCallback
    lou_registerLogCallback(customLogCallback);
    lou_registerLogCallback(NULL);

    // 3. Fuzz lou_indexTables
    // Ensure that the input is null-terminated to avoid buffer overflow
    std::vector<char> nullTerminatedData(Data, Data + Size);
    nullTerminatedData.push_back('\0');  // Ensure null-termination
    const char *tables[] = { nullTerminatedData.data(), NULL };
    lou_indexTables(tables);

    // 4. Fuzz lou_logEnd
    lou_logEnd();

    // 5. Fuzz lou_setLogLevel
    if (Size >= sizeof(logLevels)) {
        logLevels level = *reinterpret_cast<const logLevels*>(Data);
        lou_setLogLevel(level);
    }

    // 6. Fuzz lou_logFile
    // Ensure the input is null-terminated to avoid reading out of bounds
    std::vector<char> fileName(Data, Data + Size);
    fileName.push_back('\0');  // Ensure null-termination
    lou_logFile("./dummy_file");
    lou_logFile(fileName.data());

    return 0;
}