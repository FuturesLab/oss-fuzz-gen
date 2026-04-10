#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>  // For close() and mkstemp()
#include <fcntl.h>   // For O_RDWR
#include "/src/htslib/htslib/hfile.h"  // Correct path for hgetdelim

int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    // Define and initialize the parameters for hgetdelim
    char *buffer = (char *)malloc(size + 1);  // Allocate buffer for reading
    if (buffer == NULL) {
        return 0;  // Exit if memory allocation fails
    }
    size_t buffer_size = size + 1;  // Set buffer size
    int delimiter = '\n';  // Use newline as a delimiter

    // Create a temporary file and write the fuzz data to it
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        free(buffer);
        return 0;  // Exit if file creation fails
    }
    FILE *file = fdopen(fd, "w+");
    if (file == NULL) {
        close(fd);
        free(buffer);
        return 0;  // Exit if file opening fails
    }
    fwrite(data, 1, size, file);
    rewind(file);

    // Convert FILE* to hFILE* using hopen with the correct arguments
    hFILE *hfile = hopen(tmpl, "r");
    if (hfile == NULL) {
        fclose(file);
        free(buffer);
        return 0;  // Exit if hFILE conversion fails
    }

    // Call the function-under-test
    ssize_t result = hgetdelim(buffer, buffer_size, delimiter, hfile);

    // Clean up
    hclose(hfile);  // Assuming hclose is the correct function to close hFILE
    fclose(file);
    free(buffer);

    return 0;
}