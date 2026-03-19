// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_real at plist.c:505:9 in plist.h
// plist_get_real_val at plist.c:1394:6 in plist.h
// plist_set_real_val at plist.c:1613:6 in plist.h
// plist_real_val_compare at plist.c:1714:5 in plist.h
// plist_real_val_compare at plist.c:1714:5 in plist.h
// plist_to_json at jplist.c:429:13 in plist.h
// plist_mem_free at plist.c:561:6 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_read_from_file at plist.c:306:13 in plist.h
// plist_get_real_val at plist.c:1394:6 in plist.h
// plist_free at plist.c:553:6 in plist.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include <plist/plist.h>
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void fuzz_plist_new_real(double val) {
    plist_t plist = plist_new_real(val);
    if (plist) {
        double retrieved_val;
        plist_get_real_val(plist, &retrieved_val);
        plist_set_real_val(plist, val + 1.0);
        plist_real_val_compare(plist, val);
        plist_real_val_compare(plist, val + 1.0);

        char *json = nullptr;
        uint32_t length = 0;
        plist_to_json(plist, &json, &length, 0);
        if (json) {
            plist_mem_free(json);
        }

        plist_free(plist);
    }
}

static void fuzz_plist_read_from_file() {
    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "w");
    if (file) {
        const char *data = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><plist version=\"1.0\"><real>42.0</real></plist>";
        fwrite(data, 1, strlen(data), file);
        fclose(file);

        plist_t plist = nullptr;
        plist_format_t format;
        plist_err_t err = plist_read_from_file(filename, &plist, &format);
        if (err == PLIST_ERR_SUCCESS && plist) {
            double val;
            plist_get_real_val(plist, &val);
            plist_free(plist);
        }

        remove(filename);
    }
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    double val;
    memcpy(&val, Data, sizeof(double));

    fuzz_plist_new_real(val);
    fuzz_plist_read_from_file();

    return 0;
}