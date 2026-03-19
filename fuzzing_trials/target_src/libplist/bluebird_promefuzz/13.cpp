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
#include "plist/plist.h"
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