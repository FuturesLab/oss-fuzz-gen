#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = sam_hdr_init();
    const char *type = "HD";  // Example SAM header type
    const char *id = "VN";    // Example ID
    const char *val = "1.0";  // Example value

    // Check if the header was initialized successfully
    if (hdr == NULL) {
        return 0;
    }

    // Add a dummy line to the header to ensure there's something to remove
    if (sam_hdr_add_line(hdr, type, "ID", id, "VN", val, NULL) < 0) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Ensure the data is not null and has a reasonable size
    if (data != NULL && size > 0) {
        // Attempt to use the input data as part of the ID or value
        char *dynamic_id = strndup((const char *)data, size > 10 ? 10 : size);
        char *dynamic_val = strndup((const char *)data + (size > 10 ? 10 : 0), size > 20 ? 10 : size - (size > 10 ? 10 : 0));

        if (dynamic_id && dynamic_val) {
            // Add another line using dynamic data
            sam_hdr_add_line(hdr, type, "ID", dynamic_id, "VN", dynamic_val, NULL);

            // Call the function-under-test with dynamic data
            sam_hdr_remove_line_id(hdr, type, dynamic_id, dynamic_val);
        }

        free(dynamic_id);
        free(dynamic_val);
    }

    // Clean up
    sam_hdr_destroy(hdr);

    return 0;
}