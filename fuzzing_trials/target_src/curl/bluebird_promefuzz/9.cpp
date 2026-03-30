#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "curl/curl.h"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a MIME structure and a MIME part
    curl_mime *mime = curl_mime_init(NULL);
    if (!mime) return 0;

    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        return 0;
    }

    // Prepare a null-terminated string from the input data
    char *buffer = static_cast<char*>(malloc(Size + 1));
    if (!buffer) {
        curl_mime_free(mime);
        return 0;
    }
    memcpy(buffer, Data, Size);
    buffer[Size] = '\0';

    // Fuzz curl_mime_filename
    curl_mime_filename(part, buffer);

    // Fuzz curl_mime_data
    curl_mime_data(part, buffer, Size);

    // Fuzz curl_mime_encoder
    curl_mime_encoder(part, buffer);

    // Fuzz curl_mime_name
    curl_mime_name(part, buffer);

    // Create another MIME structure for subparts
    curl_mime *subparts = curl_mime_init(NULL);
    if (subparts) {
        curl_mimepart *subpart = curl_mime_addpart(subparts);
        if (subpart) {
            curl_mime_data(subpart, buffer, Size);
            // Fuzz curl_mime_subparts
            curl_mime_subparts(part, subparts);
        } else {
            curl_mime_free(subparts);
        }
    }

    // Write buffer to a dummy file
    const char *dummy_filename = "./dummy_file";
    FILE *file = fopen(dummy_filename, "wb");
    if (file) {
        fwrite(buffer, 1, Size, file);
        fclose(file);

        // Fuzz curl_mime_filedata
        curl_mime_filedata(part, dummy_filename);
    }

    // Clean up
    free(buffer);
    curl_mime_free(mime);

    return 0;
}