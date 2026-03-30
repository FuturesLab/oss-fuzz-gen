// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_init at multi.c:335:8 in multi.h
// curl_easy_init at easy.c:330:7 in easy.h
// curl_multi_cleanup at multi.c:2821:11 in multi.h
// curl_easy_cleanup at easy.c:837:6 in easy.h
// curl_multi_notify_enable at multi.c:3964:11 in multi.h
// curl_multi_add_handle at multi.c:422:11 in multi.h
// curl_multi_perform at multi.c:2811:11 in multi.h
// curl_multi_poll at multi.c:1584:11 in multi.h
// curl_multi_assign at multi.c:3635:11 in multi.h
// curl_multi_notify_disable at multi.c:3973:11 in multi.h
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
#include <curl/multi.h>

static CURLM *initialize_multi_handle() {
    return curl_multi_init();
}

static CURL *initialize_curl_handle() {
    return curl_easy_init();
}

static void cleanup_multi_handle(CURLM *multi_handle) {
    if (multi_handle) {
        curl_multi_cleanup(multi_handle);
    }
}

static void cleanup_curl_handle(CURL *curl_handle) {
    if (curl_handle) {
        curl_easy_cleanup(curl_handle);
    }
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return 0;

    CURLM *multi_handle = initialize_multi_handle();
    if (!multi_handle) return 0;

    CURL *curl_handle = initialize_curl_handle();
    if (!curl_handle) {
        cleanup_multi_handle(multi_handle);
        return 0;
    }

    unsigned int notification = *reinterpret_cast<const unsigned int *>(Data);
    CURLMcode res;

    // Fuzz curl_multi_notify_enable
    res = curl_multi_notify_enable(multi_handle, notification);

    // Fuzz curl_multi_add_handle
    res = curl_multi_add_handle(multi_handle, curl_handle);

    // Fuzz curl_multi_perform
    int running_handles;
    res = curl_multi_perform(multi_handle, &running_handles);

    // Fuzz curl_multi_poll
    struct curl_waitfd extra_fds[1];
    int numfds;
    res = curl_multi_poll(multi_handle, extra_fds, 0, 1000, &numfds);

    // Fuzz curl_multi_assign
    curl_socket_t sockfd = static_cast<curl_socket_t>(notification);
    res = curl_multi_assign(multi_handle, sockfd, reinterpret_cast<void *>(notification));

    // Fuzz curl_multi_notify_disable
    res = curl_multi_notify_disable(multi_handle, notification);

    cleanup_curl_handle(curl_handle);
    cleanup_multi_handle(multi_handle);

    return 0;
}