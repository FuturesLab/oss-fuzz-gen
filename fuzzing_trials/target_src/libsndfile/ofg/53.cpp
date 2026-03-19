#include <sndfile.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the file with libsndfile
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Try a few different string types
    const int string_types[] = {SF_STR_TITLE, SF_STR_ARTIST, SF_STR_COMMENT, SF_STR_DATE, SF_STR_ALBUM};
    size_t num_types = sizeof(string_types) / sizeof(string_types[0]);

    for (size_t i = 0; i < num_types; ++i) {
        const char *str = sf_get_string(sndfile, string_types[i]);
        if (str != NULL) {
            // Optionally, you can print or log the retrieved string
            // printf("Retrieved string: %s\n", str);
        }
    }

    // Clean up
    sf_close(sndfile);
    unlink(tmpl);

    return 0;
}