#include <sys/stat.h>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"
}

#include <cstdint>
#include <cstring>
#include <fstream>

static void writeToFile(const char* filename, const char* data, size_t size) {
    std::ofstream file(filename, std::ios::binary);
    file.write(data, size);
    file.close();
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalcomponent* comp = icalcomponent_new(kind);

    if (!comp) return 0;

    const char* strData = reinterpret_cast<const char*>(Data);
    size_t strSize = Size > 1 ? Size - 1 : 0;

    // Create a null-terminated string
    std::string safeStr(strData, strSize);

    if (strSize > 0) {
        icalcomponent_set_uid(comp, safeStr.c_str());
        icalcomponent_set_comment(comp, safeStr.c_str());
        icalcomponent_set_location(comp, safeStr.c_str());
        icalcomponent_set_summary(comp, safeStr.c_str());
        icalcomponent_set_x_name(comp, safeStr.c_str());

        const char* summary = icalcomponent_get_summary(comp);
        if (summary) {
            writeToFile("./dummy_file", summary, strlen(summary));
        }
    }

    icalcomponent_free(comp);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_3(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
