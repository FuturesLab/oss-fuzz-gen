// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_mvfprintf at mprintf.c:1230:5 in mprintf.h
// curl_unescape at escape.c:42:7 in curl.h
// curl_free at escape.c:189:6 in curl.h
// curl_easy_init at easy.c:330:7 in easy.h
// curl_easy_escape at escape.c:50:7 in curl.h
// curl_free at escape.c:189:6 in curl.h
// curl_easy_cleanup at easy.c:837:6 in easy.h
// curl_escape at escape.c:36:7 in curl.h
// curl_free at escape.c:189:6 in curl.h
// curl_easy_init at easy.c:330:7 in easy.h
// curl_easy_unescape at escape.c:163:7 in curl.h
// curl_free at escape.c:189:6 in curl.h
// curl_easy_cleanup at easy.c:837:6 in easy.h
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
#include <curl/multi.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>

static int fuzz_curl_mvfprintf(FILE *fd, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = curl_mvfprintf(fd, format, args);
    va_end(args);
    return result;
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare input data
    char *inputString = (char *)malloc(Size + 1);
    if (!inputString) return 0;
    memcpy(inputString, Data, Size);
    inputString[Size] = '\0';

    // Fuzz curl_unescape
    {
        char *unescaped = curl_unescape(inputString, Size);
        if (unescaped) {
            curl_free(unescaped);
        }
    }

    // Fuzz curl_easy_escape
    {
        CURL *curl = curl_easy_init();
        if (curl) {
            char *escaped = curl_easy_escape(curl, inputString, Size);
            if (escaped) {
                curl_free(escaped);
            }
            curl_easy_cleanup(curl);
        }
    }

    // Fuzz curl_escape
    {
        char *escaped = curl_escape(inputString, Size);
        if (escaped) {
            curl_free(escaped);
        }
    }

    // Fuzz curl_easy_unescape
    {
        CURL *curl = curl_easy_init();
        if (curl) {
            int outlength;
            char *unescaped = curl_easy_unescape(curl, inputString, Size, &outlength);
            if (unescaped) {
                curl_free(unescaped);
            }
            curl_easy_cleanup(curl);
        }
    }

    // Fuzz curl_mvfprintf
    {
        FILE *dummyFile = fopen("./dummy_file", "w");
        if (dummyFile) {
            fuzz_curl_mvfprintf(dummyFile, "%s", inputString);
            fclose(dummyFile);
        }
    }

    // Clean up
    free(inputString);

    return 0;
}