#include "ucl.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    // Create a temporary file to pass to the function
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, temp_file);

    // Rewind the file pointer to the beginning of the file
    rewind(temp_file);

    // Call the function-under-test
    struct ucl_emitter_functions *funcs = ucl_object_emit_file_funcs(temp_file);

    // Clean up
    fclose(temp_file);

    return 0;
}