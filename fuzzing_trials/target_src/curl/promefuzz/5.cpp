// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_multi_init at multi.c:335:8 in multi.h
// curl_easy_init at easy.c:330:7 in easy.h
// curl_multi_cleanup at multi.c:2821:11 in multi.h
// curl_multi_add_handle at multi.c:422:11 in multi.h
// curl_easy_cleanup at easy.c:837:6 in easy.h
// curl_multi_cleanup at multi.c:2821:11 in multi.h
// curl_multi_get_offt at multi.c:3729:11 in multi.h
// curl_multi_timeout at multi.c:3376:11 in multi.h
// curl_multi_wakeup at multi.c:1593:11 in multi.h
// curl_multi_remove_handle at multi.c:749:11 in multi.h
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
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Prepare a dummy file if needed
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (dummy_file) {
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);
    }

    // Fuzzing curl_multi_add_handle
    CURLMcode mcode = curl_multi_add_handle(multi_handle, easy_handle);
    if (mcode != CURLM_OK) {
        curl_easy_cleanup(easy_handle);
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Fuzzing curl_multi_get_offt
    curl_off_t value;
    mcode = curl_multi_get_offt(multi_handle, static_cast<CURLMinfo_offt>(Data[0] % 256), &value);

    // Fuzzing curl_multi_timeout
    long timeout;
    mcode = curl_multi_timeout(multi_handle, &timeout);

    // Fuzzing curl_multi_wakeup
    mcode = curl_multi_wakeup(multi_handle);

    // Fuzzing curl_multi_remove_handle
    mcode = curl_multi_remove_handle(multi_handle, easy_handle);

    // Cleanup
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}