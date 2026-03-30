// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:330:7 in easy.h
// curl_easy_setopt at setopt.c:2956:10 in easy.h
// curl_easy_cleanup at easy.c:837:6 in easy.h
// curl_easy_setopt at setopt.c:2956:10 in easy.h
// curl_easy_perform at easy.c:817:10 in easy.h
// curl_easy_cleanup at easy.c:837:6 in easy.h
// curl_easy_send at easy.c:1302:10 in easy.h
// curl_easy_pause at easy.c:1136:10 in curl.h
// curl_easy_pause at easy.c:1136:10 in curl.h
// curl_easy_getinfo at easy.c:853:10 in easy.h
// curl_easy_upkeep at easy.c:1320:10 in easy.h
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
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    CURL *curl = curl_easy_init();
    if (!curl) return 0;

    // Set URL to something valid; this is necessary for perform.
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");

    // Prepare a dummy file for any file-related operations.
    FILE *dummyFile = fopen("./dummy_file", "wb");
    if (!dummyFile) {
        curl_easy_cleanup(curl);
        return 0;
    }
    fwrite(Data, 1, Size, dummyFile);
    fclose(dummyFile);

    // Perform the connection using CURLOPT_CONNECT_ONLY.
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        return 0;
    }

    // Try to send data over the connected socket.
    size_t sentBytes = 0;
    curl_easy_send(curl, Data, Size, &sentBytes);

    // Pause and unpause the connection.
    curl_easy_pause(curl, CURLPAUSE_ALL);
    curl_easy_pause(curl, CURLPAUSE_CONT);

    // Get some information after the transfer.
    long responseCode;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);

    // Perform connection upkeep.
    curl_easy_upkeep(curl);

    // Cleanup
    curl_easy_cleanup(curl);

    return 0;
}