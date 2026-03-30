// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_share_init at curl_share.c:34:9 in curl.h
// curl_share_setopt at curl_share.c:59:12 in curl.h
// curl_share_strerror at strerror.c:385:13 in curl.h
// curl_share_cleanup at curl_share.c:222:12 in curl.h
// curl_share_strerror at strerror.c:385:13 in curl.h
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
#include <typecheck-gcc.h>
#include <cstdint>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(long)) return 0;

    // Initialize a CURLSH object
    CURLSH *share = curl_share_init();
    if (!share) return 0;

    // Use the data to set a CURLSHoption
    long option = *reinterpret_cast<const long *>(Data);
    CURLSHcode scode = curl_share_setopt(share, static_cast<CURLSHoption>(option), nullptr);

    // Translate the CURLSHcode into a human-readable error message
    const char *errorStr = curl_share_strerror(scode);
    if (errorStr) {
        printf("Error: %s\n", errorStr);
    }

    // Clean up the CURLSH object
    scode = curl_share_cleanup(share);
    if (scode != CURLSHE_OK) {
        printf("Cleanup Error: %s\n", curl_share_strerror(scode));
    }

    return 0;
}