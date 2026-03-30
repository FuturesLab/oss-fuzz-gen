// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_strerror at strerror.c:326:13 in multi.h
// curl_easy_setopt at setopt.c:2956:10 in easy.h
// curl_easy_setopt at setopt.c:2956:10 in easy.h
// curl_easy_strerror at strerror.c:34:13 in curl.h
// curl_version at version.c:145:7 in curl.h
// curl_easy_strerror at strerror.c:34:13 in curl.h
// curl_url_strerror at strerror.c:420:13 in urlapi.h
// curl_global_init at easy.c:197:10 in curl.h
// curl_easy_init at easy.c:330:7 in easy.h
// curl_easy_cleanup at easy.c:837:6 in easy.h
// curl_global_cleanup at easy.c:255:6 in curl.h
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
#include <curl/urlapi.h>
#include <curl/easy.h>
#include <curl/multi.h>
#include <cstdint>
#include <cstdio>

static void test_curl_multi_strerror() {
    CURLMcode codes[] = {CURLM_OK, CURLM_BAD_HANDLE, CURLM_BAD_EASY_HANDLE, CURLM_OUT_OF_MEMORY};
    for (CURLMcode code : codes) {
        const char *error_msg = curl_multi_strerror(code);
        if (error_msg) {
            printf("curl_multi_strerror: %s\n", error_msg);
        }
    }
}

static void test_curl_easy_setopt(CURL *curl) {
    if (!curl) return;
    
    CURLoption options[] = {CURLOPT_URL, CURLOPT_FOLLOWLOCATION, CURLOPT_TIMEOUT};
    for (CURLoption option : options) {
        CURLcode res;
        if (option == CURLOPT_URL) {
            // Provide a valid URL for CURLOPT_URL
            res = curl_easy_setopt(curl, option, "http://example.com");
        } else {
            res = curl_easy_setopt(curl, option, 1L);
        }
        if (res != CURLE_OK) {
            printf("curl_easy_setopt error: %s\n", curl_easy_strerror(res));
        }
    }
}

static void test_curl_version() {
    const char *version = curl_version();
    if (version) {
        printf("curl_version: %s\n", version);
    }
}

static void test_curl_easy_strerror() {
    CURLcode codes[] = {CURLE_OK, CURLE_UNSUPPORTED_PROTOCOL, CURLE_FAILED_INIT, CURLE_URL_MALFORMAT};
    for (CURLcode code : codes) {
        const char *error_msg = curl_easy_strerror(code);
        if (error_msg) {
            printf("curl_easy_strerror: %s\n", error_msg);
        }
    }
}

static void test_curl_url_strerror() {
    CURLUcode codes[] = {CURLUE_OK, CURLUE_BAD_HANDLE, CURLUE_BAD_PARTPOINTER, CURLUE_MALFORMED_INPUT};
    for (CURLUcode code : codes) {
        const char *error_msg = curl_url_strerror(code);
        if (error_msg) {
            printf("curl_url_strerror: %s\n", error_msg);
        }
    }
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    // Initialize curl globally
    if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) {
        return 0;
    }

    // Create easy handle
    CURL *curl = curl_easy_init();
    test_curl_easy_setopt(curl);
    if (curl) {
        curl_easy_cleanup(curl);
    }

    // Test other functions
    test_curl_multi_strerror();
    test_curl_version();
    test_curl_easy_strerror();
    test_curl_url_strerror();

    // Cleanup curl globally
    curl_global_cleanup();

    return 0;
}