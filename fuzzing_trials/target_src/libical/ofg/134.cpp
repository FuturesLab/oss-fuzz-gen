#include <cstdint>
#include <stddef.h>

// Assume that the following enum is defined somewhere in the project
typedef enum {
    ICALPARSER_CTRL_NONE,
    ICALPARSER_CTRL_STOP,
    ICALPARSER_CTRL_CONTINUE,
    ICALPARSER_CTRL_MAX
} DW_TAG_enumeration_typeicalparser_ctrl;

extern "C" {
    // Function-under-test
    void icalparser_set_ctrl(DW_TAG_enumeration_typeicalparser_ctrl ctrl);
}

extern "C" int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Ensure we have enough data to select a valid enum value
    if (size < 1) {
        return 0;
    }

    // Map the first byte of data to a valid enum value
    DW_TAG_enumeration_typeicalparser_ctrl ctrl = static_cast<DW_TAG_enumeration_typeicalparser_ctrl>(data[0] % ICALPARSER_CTRL_MAX);

    // Call the function-under-test
    icalparser_set_ctrl(ctrl);

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

    LLVMFuzzerTestOneInput_134(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
