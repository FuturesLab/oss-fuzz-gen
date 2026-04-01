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
#include "curl/curl.h"
#include "/src/curl/include/curl/multi.h"

static curl_mimepart* create_mime_part(curl_mime *mime) {
    return curl_mime_addpart(mime);
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize CURL
    CURL *easy_handle = curl_easy_init();
    CURLM *multi_handle = curl_multi_init();
    if (!easy_handle || !multi_handle) {
        if (easy_handle) curl_easy_cleanup(easy_handle);
        if (multi_handle) curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Create MIME structure
    curl_mime *mime = curl_mime_init(easy_handle);
    curl_mimepart *part = create_mime_part(mime);

    // Test curl_mime_data
    curl_mime_data(part, reinterpret_cast<const char*>(Data), Size);

    // Test curl_mime_filedata
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
        curl_mime_filedata(part, "./dummy_file");
    }

    // Test curl_mime_subparts
    curl_mime *subparts = curl_mime_init(easy_handle);
    curl_mimepart *subpart = create_mime_part(subparts);
    curl_mime_data(subpart, "subpart_data", 12);
    curl_mime_subparts(part, subparts);

    // Test curl_mime_headers
    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: text/plain");
    curl_mime_headers(part, headers, 1);

    // Test curl_multi_remove_handle
    curl_multi_add_handle(multi_handle, easy_handle);
    curl_multi_remove_handle(multi_handle, easy_handle);

    // Cleanup
    curl_mime_free(mime);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}