#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1044(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputData = static_cast<char *>(malloc(size + 1));
    if (inputData == nullptr) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new_xlicmimefilename(inputData);

    // Check if the property was created successfully
    if (prop != nullptr) {
        // Call the function-under-test
        const char *filename = icalproperty_get_xlicmimefilename(prop);

        // Ensure the function-under-test is utilized
        if (filename != nullptr) {
            // Perform additional operations to increase code coverage
            icalproperty_set_xlicmimefilename(prop, "new-filename");
            const char *newFilename = icalproperty_get_xlicmimefilename(prop);

            // Further operations to maximize code coverage
            if (newFilename != nullptr) {
                // Attempt to reset the filename to the original input data
                icalproperty_set_xlicmimefilename(prop, inputData);
                const char *resetFilename = icalproperty_get_xlicmimefilename(prop);

                // Check if reset was successful
                if (resetFilename != nullptr) {
                    // Further manipulation to ensure code paths are covered
                    icalproperty_set_xlicmimefilename(prop, "another-filename");
                    const char *anotherFilename = icalproperty_get_xlicmimefilename(prop);

                    // Additional checks to ensure the function is being utilized
                    if (anotherFilename != nullptr) {
                        // Attempt to set an empty filename to check edge cases
                        icalproperty_set_xlicmimefilename(prop, "");
                        const char *emptyFilename = icalproperty_get_xlicmimefilename(prop);

                        // Check if setting to empty was handled
                        if (emptyFilename != nullptr) {
                            // Try setting a very long filename
                            char longFilename[1024];
                            memset(longFilename, 'a', 1023);
                            longFilename[1023] = '\0';
                            icalproperty_set_xlicmimefilename(prop, longFilename);
                            const char *longFilenameResult = icalproperty_get_xlicmimefilename(prop);
                        }
                    }
                }
            }
        }

        // Clean up
        icalproperty_free(prop);
    }

    free(inputData);

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

    LLVMFuzzerTestOneInput_1044(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
