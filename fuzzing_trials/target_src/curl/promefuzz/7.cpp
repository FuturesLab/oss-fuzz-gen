// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:330:7 in easy.h
// curl_easy_setopt at setopt.c:2956:10 in easy.h
// curl_easy_setopt at setopt.c:2956:10 in easy.h
// curl_easy_perform at easy.c:817:10 in easy.h
// curl_easy_send at easy.c:1302:10 in easy.h
// curl_easy_recv at easy.c:1224:10 in easy.h
// curl_easy_pause at easy.c:1136:10 in curl.h
// curl_ws_send at ws.c:1761:10 in websockets.h
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
#include <curl/easy.h>
#include <curl/websockets.h>
#include <iostream>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    CURL *curl = curl_easy_init();
    if (!curl) return 0;

    char dummy_file[] = "./dummy_file";
    FILE *file = fopen(dummy_file, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    CURLcode res;
    size_t n = 0;
    size_t sent = 0;

    // Set options
    res = curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    if (res != CURLE_OK) goto cleanup;

    res = curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
    if (res != CURLE_OK) goto cleanup;

    // Perform connection
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) goto cleanup;

    // Test curl_easy_send
    res = curl_easy_send(curl, Data, Size, &n);
    if (res != CURLE_OK) goto cleanup;

    // Test curl_easy_recv
    char buffer[1024];
    res = curl_easy_recv(curl, buffer, sizeof(buffer), &n);
    if (res != CURLE_OK) goto cleanup;

    // Test curl_easy_pause
    res = curl_easy_pause(curl, CURLPAUSE_SEND);
    if (res != CURLE_OK) goto cleanup;

    // Test curl_ws_send
    res = curl_ws_send(curl, Data, Size, &sent, 1024, 0);
    if (res != CURLE_OK) goto cleanup;

cleanup:
    curl_easy_cleanup(curl);
    return 0;
}