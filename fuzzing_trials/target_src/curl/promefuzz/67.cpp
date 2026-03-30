// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_mvfprintf at mprintf.c:1230:5 in mprintf.h
// curl_mvsprintf at mprintf.c:1218:5 in mprintf.h
// curl_maprintf at mprintf.c:1161:7 in mprintf.h
// curl_msprintf at mprintf.c:1179:5 in mprintf.h
// curl_msnprintf at mprintf.c:1106:5 in mprintf.h
// curl_mfprintf at mprintf.c:1208:5 in mprintf.h
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
#include <fstream>
#include <mprintf.h>

static void test_curl_mvfprintf(FILE *file, const char *format, ...) {
    va_list args;
    va_start(args, format);
    curl_mvfprintf(file, format, args);
    va_end(args);
}

static void test_curl_mvsprintf(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    curl_mvsprintf(buffer, format, args);
    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a null-terminated format string from the input data
    char *format = (char *)malloc(Size + 1);
    if (!format) return 0;
    memcpy(format, Data, Size);
    format[Size] = '\0';

    // Test curl_maprintf
    char *maprintf_result = curl_maprintf("%s", format);
    if (maprintf_result) {
        free(maprintf_result);
    }

    // Prepare a buffer for curl_msprintf and curl_msnprintf
    char buffer[256];

    // Test curl_msprintf
    curl_msprintf(buffer, "%s", format);

    // Test curl_msnprintf with a maximum length
    curl_msnprintf(buffer, sizeof(buffer), "%s", format);

    // Test curl_mfprintf
    FILE *dummy_file = fopen("./dummy_file", "w");
    if (dummy_file) {
        curl_mfprintf(dummy_file, "%s", format);
        fclose(dummy_file);
    }

    // Test curl_mvfprintf
    dummy_file = fopen("./dummy_file", "w");
    if (dummy_file) {
        test_curl_mvfprintf(dummy_file, "%s", format);
        fclose(dummy_file);
    }

    // Test curl_mvsprintf
    test_curl_mvsprintf(buffer, "%s", format);

    free(format);
    return 0;
}