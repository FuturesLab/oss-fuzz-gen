#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "/src/htslib/htslib/hfile.h"

int LLVMFuzzerTestOneInput_218(const uint8_t *data, size_t size) {
    hFILE *file = NULL;
    size_t buffer_size = 0;
    char *buffer = NULL;

    // Create a temporary file to simulate hFILE
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Use file descriptor to open the temporary file
    int fd = fileno(temp_file);
    if (fd == -1) {
        fclose(temp_file);
        return 0;
    }

    // Use hdopen to open the temporary file by its file descriptor
    file = hdopen(fd, "r");
    if (file == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Read data from hFILE to ensure the function is invoked with actual content
    char read_buffer[1024];
    ssize_t bytes_read = hread(file, read_buffer, sizeof(read_buffer));
    if (bytes_read > 0) {
        // Process the read data if necessary
    }

    // Call the function-under-test
    buffer = hfile_mem_steal_buffer(file, &buffer_size);

    // Clean up
    if (buffer != NULL) {
        free(buffer);
    }
    hclose(file);
    fclose(temp_file);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_218(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
