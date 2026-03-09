#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for the two ucl_object_t parameters
    size_t mid = size / 2;
    const uint8_t *data1 = data;
    size_t size1 = mid;
    const uint8_t *data2 = data + mid;
    size_t size2 = size - mid;

    // Create ucl_object_t objects from the input data
    ucl_object_t *obj1 = ucl_object_fromstring_common((const char *)data1, size1, 0);
    ucl_object_t *obj2 = ucl_object_fromstring_common((const char *)data2, size2, 0);

    // Ensure that the string for the third parameter is null-terminated
    char comment[256];
    size_t comment_len = size < 256 ? size : 255;
    memcpy(comment, data, comment_len);
    comment[comment_len] = '\0';

    // Call the function-under-test
    ucl_comments_add(obj1, obj2, comment);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}