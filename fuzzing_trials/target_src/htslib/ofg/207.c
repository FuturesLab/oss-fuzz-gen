#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Added for memcpy
#include <unistd.h>  // Added for off_t
#include "/src/htslib/htslib/hfile.h"  // Corrected path for hfile.h

int LLVMFuzzerTestOneInput_207(const uint8_t *data, size_t size) {
    if (size < sizeof(off_t) + sizeof(int)) {
        return 0; // Not enough data to proceed
    }

    // Create a temporary file to use with hFILE
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Open the temporary file as an hFILE
    hFILE *hfile = hopen(temp_file, "r");
    if (hfile == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Extract off_t and int from the data
    off_t offset;
    int whence;

    // Assuming the first sizeof(off_t) bytes are for offset
    memcpy(&offset, data, sizeof(off_t));

    // The next sizeof(int) bytes are for whence
    memcpy(&whence, data + sizeof(off_t), sizeof(int));

    // Call the function-under-test
    hseek(hfile, offset, whence);

    // Clean up
    hclose(hfile);
    fclose(temp_file);

    return 0;
}