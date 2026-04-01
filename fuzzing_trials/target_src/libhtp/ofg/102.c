#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <htp/htp.h>

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid user data
    if (size < sizeof(void *)) {
        return 0;
    }

    // Initialize htp_connp_t structure
    htp_connp_t *connp = htp_connp_create(NULL);
    if (connp == NULL) {
        return 0;
    }

    // Use the first part of the data as user data
    const void *user_data = (const void *)data;

    // Call the function-under-test
    htp_connp_set_user_data(connp, user_data);

    // Clean up
    htp_connp_destroy_all(connp);

    return 0;
}