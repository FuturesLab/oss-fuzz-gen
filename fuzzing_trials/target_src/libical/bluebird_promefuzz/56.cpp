#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalduration.h"

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct icaldurationtype) + sizeof(struct icaltimetype) * 2) {
        return 0;
    }

    struct icaldurationtype *dur = (struct icaldurationtype *)Data;
    struct icaltimetype *t1 = (struct icaltimetype *)(Data + sizeof(struct icaldurationtype));
    struct icaltimetype *t2 = (struct icaltimetype *)(Data + sizeof(struct icaldurationtype) + sizeof(struct icaltimetype));

    // Normalize duration
    struct icaldurationtype normalizedDur = icaldurationtype_normalize(*dur);

    // Extend time by duration
    struct icaltimetype extendedTime = icalduration_extend(*t1, *dur);

    // Create null duration
    struct icaldurationtype nullDur = icaldurationtype_null_duration();
    assert(nullDur.days == 0 && nullDur.is_neg == 0);

    // Calculate duration from two times
    struct icaldurationtype durationFromTimes = icalduration_from_times(*t1, *t2);

    // Create bad duration
    struct icaldurationtype badDur = icaldurationtype_bad_duration();
    assert(icaldurationtype_is_bad_duration(badDur));

    // Write to a dummy file if necessary
    std::ofstream dummyFile("./dummy_file", std::ios::binary);
    if (dummyFile.is_open()) {
        dummyFile.write(reinterpret_cast<const char *>(Data), Size);
        dummyFile.close();
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

    LLVMFuzzerTestOneInput_56(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
