// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_mime_init at mime.c:1180:12 in curl.h
// curl_mime_addpart at mime.c:1214:16 in curl.h
// curl_mime_free at mime.c:1082:6 in curl.h
// curl_mime_free at mime.c:1082:6 in curl.h
// curl_mime_filename at mime.c:1256:10 in curl.h
// curl_mime_data at mime.c:1273:10 in curl.h
// curl_mime_encoder at mime.c:1374:10 in curl.h
// curl_mime_name at mime.c:1239:10 in curl.h
// curl_mime_init at mime.c:1180:12 in curl.h
// curl_mime_addpart at mime.c:1214:16 in curl.h
// curl_mime_data at mime.c:1273:10 in curl.h
// curl_mime_subparts at mime.c:1489:10 in curl.h
// curl_mime_free at mime.c:1082:6 in curl.h
// curl_mime_filedata at mime.c:1300:10 in curl.h
// curl_mime_free at mime.c:1082:6 in curl.h
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
#include <cstring>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
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