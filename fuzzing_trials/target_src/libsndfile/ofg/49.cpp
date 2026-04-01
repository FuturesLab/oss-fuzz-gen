#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for 'close' function

extern "C" {
    #include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit the fuzzer
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile != nullptr) {
        // Call the function-under-test
        (void)sf_current_byterate(sndfile); // Use the value to avoid unused variable warning

        // Close the SNDFILE
        sf_close(sndfile);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}