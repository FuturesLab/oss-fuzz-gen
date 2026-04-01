#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

// Remove the 'extern "C"' linkage specification for C++ 
// because this is a C file and it is not needed.
int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    gzFile file;
    int error_code = 0;
    const char *error_message;

    // Open a temporary file to use with gzFile
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Open the temporary file with gzdopen
    file = gzdopen(fileno(temp_file), "rb");
    if (file == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Call the function-under-test
    error_message = gzerror(file, &error_code);

    // Print the error message and code for debugging purposes
    if (error_message != NULL) {
        printf("Error message: %s, Error code: %d\n", error_message, error_code);
    }

    // Clean up
    gzclose(file);
    fclose(temp_file);

    return 0;
}