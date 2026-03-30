// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_mvsnprintf at mprintf.c:1081:5 in mprintf.h
// curl_mprintf at mprintf.c:1198:5 in mprintf.h
// curl_mfprintf at mprintf.c:1208:5 in mprintf.h
// curl_mvprintf at mprintf.c:1225:5 in mprintf.h
// curl_mvaprintf at mprintf.c:1143:7 in mprintf.h
// curl_mvsprintf at mprintf.c:1218:5 in mprintf.h
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
#include <curl/mprintf.h>

static void fuzz_curl_mvsnprintf(const char *format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    curl_mvsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
}

static void fuzz_curl_mprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    curl_mprintf(format, args);
    va_end(args);
}

static void fuzz_curl_mfprintf(const char *format, ...) {
    FILE *dummyFile = fopen("./dummy_file", "w");
    if (dummyFile) {
        va_list args;
        va_start(args, format);
        curl_mfprintf(dummyFile, format, args);
        va_end(args);
        fclose(dummyFile);
    }
}

static void fuzz_curl_mvprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    curl_mvprintf(format, args);
    va_end(args);
}

static void fuzz_curl_mvaprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *formattedString = curl_mvaprintf(format, args);
    if (formattedString) {
        free(formattedString);
    }
    va_end(args);
}

static void fuzz_curl_mvsprintf(const char *format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    curl_mvsprintf(buffer, format, args);
    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Ensure null-termination of the format string
    std::vector<char> format(Data, Data + Size);
    format.push_back('\0');

    // Validate format string to avoid undefined behavior
    bool validFormat = true;
    for (size_t i = 0; i < format.size() - 1; ++i) {
        if (format[i] == '%' && (i + 1 >= format.size() - 1 || 
            (format[i + 1] != 'd' && format[i + 1] != 's' && format[i + 1] != 'c' && format[i + 1] != '%'))) {
            validFormat = false;
            break;
        }
    }

    if (!validFormat) return 0;

    // Fuzz each function
    fuzz_curl_mvsnprintf(format.data(), 0);
    fuzz_curl_mprintf(format.data(), 0);
    fuzz_curl_mfprintf(format.data(), 0);
    fuzz_curl_mvprintf(format.data(), 0);
    fuzz_curl_mvaprintf(format.data(), 0);
    fuzz_curl_mvsprintf(format.data(), 0);

    return 0;
}