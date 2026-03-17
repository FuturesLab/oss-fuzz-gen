#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Include this for the close() and unlink() functions
#include <fcntl.h>  // Include this for mkstemp() function
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = 1; // Set to true
    u32 track_num = 1;  // Initialize with a non-zero value
    char outName[] = "output.xml"; // Output file name
    Bool is_binary = 0; // Initialize with false

    // Create a temporary file to simulate the input ISO file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the ISO file from the temporary file
    file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (file == NULL) {
        return 0;
    }

    // Call the function under test
    gf_isom_extract_meta_xml(file, root_meta, track_num, outName, &is_binary);

    // Clean up
    gf_isom_close(file);
    unlink(tmpl); // Remove the temporary file

    return 0;
}