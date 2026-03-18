#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <ares.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    ares_channel channel;
    int status = ares_init(&channel);
    if (status != ARES_SUCCESS) {
        return 0;
    }

    /* Call the function under test */
    ares_cancel(channel);

    /* Clean up */
    ares_destroy(channel);

    return 0;
}