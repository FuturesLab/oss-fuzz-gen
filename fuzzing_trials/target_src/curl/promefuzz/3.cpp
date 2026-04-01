// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:330:7 in easy.h
// curl_multi_init at multi.c:335:8 in multi.h
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
#include "typecheck-gcc.h"
#include <cstdint>
#include <stdexcept>

static CURLcode dummy_curl_easy_setopt(CURL *handle, CURLoption option, ...) {
    return CURLE_OK;
}

static CURLMcode dummy_curl_multi_setopt(CURLM *multi_handle, CURLMoption option, ...) {
    return CURLM_OK;
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(CURLoption)) {
        return 0;
    }

    CURL *easy_handle = curl_easy_init();
    CURLM *multi_handle = curl_multi_init();
    if (!easy_handle || !multi_handle) {
        return 0;
    }

    CURLoption option = *reinterpret_cast<const CURLoption*>(Data);
    const uint8_t *option_data = Data + sizeof(CURLoption);
    size_t option_data_size = Size - sizeof(CURLoption);

    try {
        if (curlcheck_string_option(option) && option_data_size > 0) {
            const char *str_arg = reinterpret_cast<const char*>(option_data);
            dummy_curl_easy_setopt(easy_handle, option, str_arg);
        } else if (curlcheck_long_option(option) && option_data_size >= sizeof(long)) {
            long long_arg = *reinterpret_cast<const long*>(option_data);
            dummy_curl_easy_setopt(easy_handle, option, long_arg);
        } else if (curlcheck_off_t_option(option) && option_data_size >= sizeof(curl_off_t)) {
            curl_off_t off_t_arg = *reinterpret_cast<const curl_off_t*>(option_data);
            dummy_curl_easy_setopt(easy_handle, option, off_t_arg);
        } else if (curlcheck_cb_data_option(option)) {
            void *data_arg = const_cast<uint8_t*>(option_data);
            dummy_curl_easy_setopt(easy_handle, option, data_arg);
        } else if (curlcheck_slist_option(option)) {
            struct curl_slist *slist_arg = nullptr;
            dummy_curl_easy_setopt(easy_handle, option, slist_arg);
        }

        if (curlcheck_cb_data_option(option)) {
            void *multi_data_arg = const_cast<uint8_t*>(option_data);
            dummy_curl_multi_setopt(multi_handle, static_cast<CURLMoption>(option), multi_data_arg);
        }
    } catch (const std::exception &) {
        // Handle any exceptions that may occur
    }

    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}