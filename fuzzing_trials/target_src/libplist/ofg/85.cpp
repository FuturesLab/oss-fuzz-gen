#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *json_data = (char *)malloc(size + 1);
    if (json_data == NULL) {
        return 0;
    }
    memcpy(json_data, data, size);
    json_data[size] = '\0';

    plist_t plist = NULL;
    uint32_t json_length = (uint32_t)size;

    // Call the function-under-test
    plist_err_t result = plist_from_json(json_data, json_length, &plist);

    // Cleanup
    free(json_data);
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}