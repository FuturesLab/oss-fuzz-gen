#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    gzFile file;
    int error_code;
    const char *error_msg;

    // Create a temporary file to use with gzFile
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Open the temporary file with gzopen
    file = gzdopen(fileno(temp_file), "rb");
    if (file == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Call the function-under-test
    error_msg = gzerror(file, &error_code);

    // Use the error message and code to prevent unused variable warnings
    if (error_msg != NULL) {
        printf("Error message: %s\n", error_msg);
    }
    printf("Error code: %d\n", error_code);

    // Close the gzFile and the temporary file
    gzclose(file);
    fclose(temp_file);

    return 0;
}