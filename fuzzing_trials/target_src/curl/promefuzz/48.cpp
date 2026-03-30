// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_strnequal at strequal.c:87:5 in curl.h
// curl_easy_option_by_name at easygetopt.c:53:31 in options.h
// curl_strequal at strequal.c:76:5 in curl.h
// curl_url at urlapi.c:1288:8 in urlapi.h
// curl_url_set at urlapi.c:1805:11 in urlapi.h
// curl_url_get at urlapi.c:1541:11 in urlapi.h
// curl_free at escape.c:189:6 in curl.h
// curl_url_get at urlapi.c:1541:11 in urlapi.h
// curl_free at escape.c:189:6 in curl.h
// curl_url_cleanup at urlapi.c:1293:6 in urlapi.h
// curl_slist_append at slist.c:85:20 in curl.h
// curl_slist_free_all at slist.c:124:6 in curl.h
// curl_easy_init at easy.c:330:7 in easy.h
// curl_easy_escape at escape.c:50:7 in curl.h
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
#include <curl/urlapi.h>
#include <curl/options.h>
#include <cstddef>
#include <cstring>
#include <cstdio>

static void fuzz_curl_strnequal(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    size_t n = Size / 2;
    const char *s1 = reinterpret_cast<const char*>(Data);
    const char *s2 = reinterpret_cast<const char*>(Data + n);
    curl_strnequal(s1, s2, n);
}

static void fuzz_curl_easy_option_by_name(const uint8_t *Data, size_t Size) {
    char *name = new char[Size + 1];
    memcpy(name, Data, Size);
    name[Size] = '\0';
    curl_easy_option_by_name(name);
    delete[] name;
}

static void fuzz_curl_strequal(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    size_t n = Size / 2;
    char *s1 = new char[n + 1];
    char *s2 = new char[Size - n + 1];
    memcpy(s1, Data, n);
    s1[n] = '\0';
    memcpy(s2, Data + n, Size - n);
    s2[Size - n] = '\0';
    curl_strequal(s1, s2);
    delete[] s1;
    delete[] s2;
}

static void fuzz_curl_url_get(const uint8_t *Data, size_t Size) {
    CURLU *handle = curl_url();
    if (handle) {
        char *url = new char[Size + 1];
        memcpy(url, Data, Size);
        url[Size] = '\0';
        curl_url_set(handle, CURLUPART_URL, url, 0);

        char *part;
        curl_url_get(handle, CURLUPART_SCHEME, &part, 0);
        if (part) curl_free(part);

        curl_url_get(handle, CURLUPART_HOST, &part, 0);
        if (part) curl_free(part);

        curl_url_cleanup(handle);
        delete[] url;
    }
}

static void fuzz_curl_slist_append(const uint8_t *Data, size_t Size) {
    struct curl_slist *list = nullptr;
    char *data = new char[Size + 1];
    memcpy(data, Data, Size);
    data[Size] = '\0';
    list = curl_slist_append(list, data);
    curl_slist_free_all(list);
    delete[] data;
}

static void fuzz_curl_easy_escape(const uint8_t *Data, size_t Size) {
    CURL *handle = curl_easy_init();
    if (handle) {
        char *input = new char[Size + 1];
        memcpy(input, Data, Size);
        input[Size] = '\0';
        char *escaped = curl_easy_escape(handle, input, static_cast<int>(Size));
        if (escaped) {
            curl_free(escaped);
        }
        curl_easy_cleanup(handle);
        delete[] input;
    }
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    fuzz_curl_strnequal(Data, Size);
    fuzz_curl_easy_option_by_name(Data, Size);
    fuzz_curl_strequal(Data, Size);
    fuzz_curl_url_get(Data, Size);
    fuzz_curl_slist_append(Data, Size);
    fuzz_curl_easy_escape(Data, Size);
    return 0;
}