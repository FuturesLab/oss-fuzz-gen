#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <htp/htp.h>

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Initialize a connection parser object
    htp_connp_t *connp = htp_connp_create(NULL);
    if (connp == NULL) {
        return 0;
    }

    // Set some user data to ensure it's not NULL
    int user_data = 42;
    htp_connp_set_user_data(connp, &user_data);

    // Call the function-under-test
    void *result = htp_connp_get_user_data(connp);

    // Clean up
    htp_connp_destroy(connp);

    return 0;
}