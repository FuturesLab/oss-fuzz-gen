// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_maprintf at mprintf.c:1161:7 in mprintf.h
// curl_msnprintf at mprintf.c:1106:5 in mprintf.h
// curl_mvprintf at mprintf.c:1225:5 in mprintf.h
// curl_mvaprintf at mprintf.c:1143:7 in mprintf.h
// curl_mvfprintf at mprintf.c:1230:5 in mprintf.h
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

static void test_variadic_functions(const char *format, ...) {
    char buffer[1024] = {0};

    va_list args;
    va_start(args, format);

    // Test curl_maprintf
    char *maprintf_result = curl_maprintf(format);
    if (maprintf_result) {
        free(maprintf_result);
    }

    // Test curl_msnprintf
    curl_msnprintf(buffer, sizeof(buffer), format);

    // Test curl_mvprintf
    curl_mvprintf(format, args);

    // Test curl_mvaprintf
    char *mvaprintf_result = curl_mvaprintf(format, args);
    if (mvaprintf_result) {
        free(mvaprintf_result);
    }

    // Test curl_mvfprintf
    FILE *dummy_file = fopen("./dummy_file", "w");
    if (dummy_file) {
        curl_mvfprintf(dummy_file, format, args);
        fclose(dummy_file);
    }

    // Test curl_mvsprintf
    curl_mvsprintf(buffer, format, args);

    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure the input data is null-terminated
    std::vector<uint8_t> data_with_null(Data, Data + Size);
    data_with_null.push_back('\0');

    // Create a format string for testing
    const char *format = reinterpret_cast<const char *>(data_with_null.data());

    // Test the functions with the provided format
    test_variadic_functions(format, 0);

    return 0;
}