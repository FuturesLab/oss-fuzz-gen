// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fget_mdc_logging_status at H5F.c:2364:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fstart_mdc_logging at H5F.c:2292:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_mdc_logging_status at H5F.c:2364:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fstop_mdc_logging at H5F.c:2328:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_mdc_logging_status at H5F.c:2364:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "H5Fpublic.h"
#include "H5Ppublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "dummy content");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file();

    hid_t file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    bool is_enabled = false;
    bool is_currently_logging = false;

    if (H5Fget_mdc_logging_status(file_id, &is_enabled, &is_currently_logging) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    if (H5Fstart_mdc_logging(file_id) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    if (H5Fget_mdc_logging_status(file_id, &is_enabled, &is_currently_logging) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    if (H5Fstop_mdc_logging(file_id) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    if (H5Fget_mdc_logging_status(file_id, &is_enabled, &is_currently_logging) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    H5Fclose(file_id);
    return 0;
}