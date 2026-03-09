#include "ucl.h"
#include <stdio.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    // Create a temporary file to pass to the function
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    fwrite(data, 1, size, temp_file);

    // Reset the file pointer to the beginning of the file
    rewind(temp_file);

    // Call the function-under-test
    struct ucl_emitter_functions *funcs = ucl_object_emit_file_funcs(temp_file);

    // Clean up
    if (funcs != NULL) {
        // Assuming there is a function to free the emitter functions
        // If not, this part should be adjusted according to the library's API
        // ucl_emitter_functions_free(funcs);
    }

    fclose(temp_file);

    return 0;
}