// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:330:7 in easy.h
// curl_easy_cleanup at easy.c:837:6 in easy.h
// curl_mvfprintf at mprintf.c:1230:5 in mprintf.h
// curl_strequal at strequal.c:76:5 in curl.h
// curl_unescape at escape.c:42:7 in curl.h
// curl_free at escape.c:189:6 in curl.h
// curl_easy_escape at escape.c:50:7 in curl.h
// curl_free at escape.c:189:6 in curl.h
// curl_escape at escape.c:36:7 in curl.h
// curl_free at escape.c:189:6 in curl.h
// curl_easy_unescape at escape.c:163:7 in curl.h
// curl_free at escape.c:189:6 in curl.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <curl/curl.h>
#include <curl/mprintf.h>
#include <cstdarg>

static CURL* initialize_curl() {
    return curl_easy_init();
}

static void cleanup_curl(CURL* handle) {
    if (handle) {
        curl_easy_cleanup(handle);
    }
}

static void test_curl_mvfprintf(FILE* file, const char* format, ...) {
    va_list args;
    va_start(args, format);
    curl_mvfprintf(file, format, args);
    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure strings are null-terminated
    std::vector<char> str1_vec(Data, Data + Size);
    str1_vec.push_back('\0');
    const char* str1 = str1_vec.data();

    // Create str2 safely
    std::vector<char> str2_vec;
    if (Size > 1) {
        str2_vec.assign(Data + 1, Data + Size);
        str2_vec.push_back('\0');
    }
    const char* str2 = str2_vec.empty() ? str1 : str2_vec.data();

    // Test curl_strequal
    int strequal_result = curl_strequal(str1, str2);

    // Test curl_unescape
    char* unescaped = curl_unescape(str1, Size);
    if (unescaped) {
        curl_free(unescaped);
    }

    // Initialize CURL handle
    CURL* curl_handle = initialize_curl();
    if (!curl_handle) return 0;

    // Test curl_easy_escape
    char* escaped_easy = curl_easy_escape(curl_handle, str1, Size);
    if (escaped_easy) {
        curl_free(escaped_easy);
    }

    // Test curl_escape
    char* escaped = curl_escape(str1, Size);
    if (escaped) {
        curl_free(escaped);
    }

    // Test curl_easy_unescape
    int outlength;
    char* unescaped_easy = curl_easy_unescape(curl_handle, str1, Size, &outlength);
    if (unescaped_easy) {
        curl_free(unescaped_easy);
    }

    // Test curl_mvfprintf
    FILE* dummy_file = fopen("./dummy_file", "w");
    if (dummy_file) {
        test_curl_mvfprintf(dummy_file, "%s", str1);
        fclose(dummy_file);
    }

    // Cleanup
    cleanup_curl(curl_handle);

    return 0;
}