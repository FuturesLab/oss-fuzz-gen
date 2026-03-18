#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to split into two parts
    if (size < 2) {
        return 0;
    }

    // Create two ucl_object_t objects
    ucl_object_t *obj1 = ucl_object_new();
    ucl_object_t *obj2 = ucl_object_new();

    // Split the data into two parts
    size_t mid = size / 2;
    const char *comment = (const char *)(data + mid);

    // Null-terminate the comment string
    char *comment_str = (char *)malloc(size - mid + 1);
    if (comment_str == NULL) {
        ucl_object_unref(obj1);
        ucl_object_unref(obj2);
        return 0;
    }
    memcpy(comment_str, comment, size - mid);
    comment_str[size - mid] = '\0';

    // Call the function under test
    ucl_comments_add(obj1, obj2, comment_str);

    // Clean up
    free(comment_str);
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}