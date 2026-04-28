#include <libical/ical.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // Include for write, close, and unlink functions
#include <fcntl.h>  // Include for mkstemp function

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_234(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create an icalattach
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to simulate an attachment
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Create an icalattach from the file
    icalattach *attachment = icalattach_new_from_url(tmpl);

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_image(attachment, NULL);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }

    // Remove the temporary file and free the attachment
    unlink(tmpl);
    icalattach_unref(attachment);

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

    LLVMFuzzerTestOneInput_234(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
