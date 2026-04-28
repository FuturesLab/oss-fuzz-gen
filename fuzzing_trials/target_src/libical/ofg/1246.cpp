#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_1246(const uint8_t *data, size_t size) {
    // Define and initialize the struct icaldatetimeperiodtype
    struct icaldatetimeperiodtype dtp;
    memset(&dtp, 0, sizeof(dtp));

    // Ensure that size is sufficient to extract data for struct fields
    if (size < sizeof(struct icaltimetype) + sizeof(struct icalperiodtype)) {
        return 0;
    }

    // Initialize icaltimetype part of icaldatetimeperiodtype
    memcpy(&dtp.time, data, sizeof(struct icaltimetype));
    data += sizeof(struct icaltimetype);
    size -= sizeof(struct icaltimetype);

    // Initialize icalperiodtype part of icaldatetimeperiodtype
    memcpy(&dtp.period, data, sizeof(struct icalperiodtype));
    data += sizeof(struct icalperiodtype);
    size -= sizeof(struct icalperiodtype);

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_rdate(dtp, NULL);

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
    }

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

    LLVMFuzzerTestOneInput_1246(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
