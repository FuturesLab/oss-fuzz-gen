#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" {
    #include "plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for meaningful fuzzing
    if (size < 1) return 0;

    // Create a temporary file to write the plist data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    // Close the file descriptor as we only need the filename
    close(fd);

    // Create a plist object from the input data
    plist_t plist = plist_new_data(reinterpret_cast<const char*>(data), size);
    if (!plist) {
        // Clean up the temporary file if plist creation fails
        unlink(tmpl);
        return 0;
    }

    // Define plist format and write options
    plist_format_t format = PLIST_FORMAT_XML;
    plist_write_options_t options = static_cast<plist_write_options_t>(0); // Assuming 0 is the default option

    // Call the function-under-test
    plist_err_t err = plist_write_to_file(plist, tmpl, format, options);

    // Clean up
    plist_free(plist);
    unlink(tmpl);

    return 0;
}