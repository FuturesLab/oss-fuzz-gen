// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_easy_init at easy.c:330:7 in easy.h
// curl_easy_setopt at setopt.c:2956:10 in easy.h
// curl_easy_setopt at setopt.c:2956:10 in easy.h
// curl_easy_cleanup at easy.c:837:6 in easy.h
// curl_easy_send at easy.c:1302:10 in easy.h
// curl_easy_strerror at strerror.c:34:13 in curl.h
// curl_ws_recv at ws.c:1528:10 in websockets.h
// curl_easy_strerror at strerror.c:34:13 in curl.h
// curl_version_info at version.c:596:25 in curl.h
// curl_ws_send at ws.c:1761:10 in websockets.h
// curl_easy_strerror at strerror.c:34:13 in curl.h
// curl_mime_init at mime.c:1180:12 in curl.h
// curl_mime_addpart at mime.c:1214:16 in curl.h
// curl_mime_headers at mime.c:1397:10 in curl.h
// curl_easy_strerror at strerror.c:34:13 in curl.h
// curl_mime_free at mime.c:1082:6 in curl.h
// curl_easy_header at headers.c:55:11 in header.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <cstring>
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/websockets.h>
#include <curl/header.h>

static CURL *initialize_curl() {
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
        curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
    }
    return curl;
}

static void cleanup_curl(CURL *curl) {
    curl_easy_cleanup(curl);
}

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    CURL *curl = initialize_curl();
    if (!curl) {
        return 0;
    }

    // Prepare a buffer to send/receive data
    char buffer[1024];
    size_t n = 0;
    CURLcode res;

    // Fuzz curl_easy_send
    if (Size > 0) {
        res = curl_easy_send(curl, Data, Size, &n);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_send failed: " << curl_easy_strerror(res) << std::endl;
        }
    }

    // Fuzz curl_ws_recv
    const struct curl_ws_frame *metap = nullptr;
    res = curl_ws_recv(curl, buffer, sizeof(buffer), &n, &metap);
    if (res != CURLE_OK) {
        std::cerr << "curl_ws_recv failed: " << curl_easy_strerror(res) << std::endl;
    }

    // Fuzz curl_version_info
    curl_version_info_data *version_info = curl_version_info(CURLVERSION_NOW);
    if (version_info) {
        std::cout << "Curl version: " << version_info->version << std::endl;
    }

    // Fuzz curl_ws_send
    res = curl_ws_send(curl, Data, Size, &n, 0, 0);
    if (res != CURLE_OK) {
        std::cerr << "curl_ws_send failed: " << curl_easy_strerror(res) << std::endl;
    }

    // Fuzz curl_mime_headers
    curl_mime *mime = curl_mime_init(curl);
    curl_mimepart *part = curl_mime_addpart(mime);
    struct curl_slist *headers = nullptr;
    res = curl_mime_headers(part, headers, 1);
    if (res != CURLE_OK) {
        std::cerr << "curl_mime_headers failed: " << curl_easy_strerror(res) << std::endl;
    }
    curl_mime_free(mime);

    // Fuzz curl_easy_header
    struct curl_header *hout = nullptr;
    CURLHcode hres = curl_easy_header(curl, "Content-Type", 0, 0, 0, &hout);
    if (hres != CURLHE_OK) {
        std::cerr << "curl_easy_header failed" << std::endl;
    }

    cleanup_curl(curl);
    return 0;
}