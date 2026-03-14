#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to create a cmsSEQ object
    if (size < sizeof(cmsSEQ)) {
        return 0;
    }

    // Allocate memory for a cmsSEQ object
    cmsSEQ *seq = (cmsSEQ *)malloc(sizeof(cmsSEQ));
    if (seq == NULL) {
        return 0;
    }

    // Initialize the cmsSEQ object with data
    memcpy(seq, data, sizeof(cmsSEQ));

    // Call the function-under-test
    cmsSEQ *dup_seq = cmsDupProfileSequenceDescription(seq);

    // Clean up
    if (dup_seq != NULL) {
        cmsFreeProfileSequenceDescription(dup_seq);
    }

    free(seq);

    return 0;
}