// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:330:7 in easy.h
// curl_multi_init at multi.c:335:8 in multi.h
// curl_easy_cleanup at easy.c:837:6 in easy.h
// curl_multi_cleanup at multi.c:2821:11 in multi.h
// curl_easy_header at headers.c:55:11 in header.h
// curl_multi_poll at multi.c:1584:11 in multi.h
// curl_multi_waitfds at multi.c:1267:11 in multi.h
// curl_multi_notify_disable at multi.c:3973:11 in multi.h
// curl_easy_cleanup at easy.c:837:6 in easy.h
// curl_multi_cleanup at multi.c:2821:11 in multi.h
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
#include <curl/multi.h>
#include <stdint.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURL *easy_handle = curl_easy_init();
    CURLM *multi_handle = curl_multi_init();

    if (!easy_handle || !multi_handle) {
        if (easy_handle) curl_easy_cleanup(easy_handle);
        if (multi_handle) curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Fuzzing curl_easy_header
    if (Size > 5) {
        const char *header_name = reinterpret_cast<const char *>(Data);
        size_t index = Data[Size - 1] % 10;
        unsigned int origin = Data[Size - 2] % 2;
        int request = Data[Size - 3] % 2;
        struct curl_header *header_out = NULL;

        curl_easy_header(easy_handle, header_name, index, origin, request, &header_out);
    }

    // Fuzzing curl_multi_poll
    struct curl_waitfd extra_fds[1];
    int ret;
    curl_multi_poll(multi_handle, extra_fds, 1, 1000, &ret);

    // Fuzzing curl_multi_waitfds
    struct curl_waitfd ufds[1];
    unsigned int fd_count;
    curl_multi_waitfds(multi_handle, ufds, 1, &fd_count);

    // Fuzzing curl_multi_notify_disable
    unsigned int notification = Data[0] % 256;
    curl_multi_notify_disable(multi_handle, notification);

    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}