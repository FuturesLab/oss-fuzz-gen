// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_init at multi.c:335:8 in multi.h
// curl_multi_cleanup at multi.c:2821:11 in multi.h
// curl_multi_wait at multi.c:1574:11 in multi.h
// curl_multi_socket_action at multi.c:3273:11 in multi.h
// curl_multi_setopt at multi.c:3168:11 in multi.h
// curl_multi_socket_all at multi.c:3284:11 in multi.h
// curl_multi_info_read at multi.c:2925:10 in multi.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <curl/multi.h>
#include <cstdint>
#include <cstdio>
#include <cstring>

static CURLM *initialize_multi_handle() {
    CURLM *multi_handle = curl_multi_init();
    return multi_handle;
}

static void cleanup_multi_handle(CURLM *multi_handle) {
    if (multi_handle) {
        curl_multi_cleanup(multi_handle);
    }
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0; // Ensure there's enough data for at least an integer

    CURLM *multi_handle = initialize_multi_handle();
    if (!multi_handle) return 0;

    int running_handles = 0;
    int timeout_ms = 1000;
    struct curl_waitfd extra_fds[1];
    extra_fds[0].fd = 0;
    extra_fds[0].events = CURL_WAIT_POLLIN;
    extra_fds[0].revents = 0;

    // Fuzz curl_multi_wait
    CURLMcode mcode = curl_multi_wait(multi_handle, extra_fds, 1, timeout_ms, &running_handles);
    if (mcode != CURLM_OK) {
        cleanup_multi_handle(multi_handle);
        return 0;
    }

    // Fuzz curl_multi_socket
    curl_socket_t s = 0;
    mcode = curl_multi_socket(multi_handle, s, &running_handles);
    if (mcode != CURLM_OK) {
        cleanup_multi_handle(multi_handle);
        return 0;
    }

    // Fuzz curl_multi_setopt
    CURLMoption option = static_cast<CURLMoption>(Data[0]);
    mcode = curl_multi_setopt(multi_handle, option, nullptr);
    if (mcode != CURLM_OK) {
        cleanup_multi_handle(multi_handle);
        return 0;
    }

    // Fuzz curl_multi_socket_all
    mcode = curl_multi_socket_all(multi_handle, &running_handles);
    if (mcode != CURLM_OK) {
        cleanup_multi_handle(multi_handle);
        return 0;
    }

    // Fuzz curl_multi_info_read
    int msgs_in_queue = 0;
    CURLMsg *msg;
    do {
        msg = curl_multi_info_read(multi_handle, &msgs_in_queue);
    } while (msg);

    cleanup_multi_handle(multi_handle);
    return 0;
}