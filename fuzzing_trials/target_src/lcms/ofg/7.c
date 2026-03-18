#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a cmsSEQ object
    if (size < sizeof(cmsSEQ)) {
        return 0;
    }

    // Allocate memory for a cmsSEQ object
    cmsSEQ *seq = (cmsSEQ *)malloc(sizeof(cmsSEQ));
    if (seq == NULL) {
        return 0;
    }

    // Initialize the cmsSEQ object with the provided data
    memcpy(seq, data, sizeof(cmsSEQ));

    // Call the function-under-test
    cmsSEQ *dupSeq = cmsDupProfileSequenceDescription(seq);

    // Clean up
    if (dupSeq != NULL) {
        cmsFreeProfileSequenceDescription(dupSeq);
    }
    free(seq);

    return 0;
}