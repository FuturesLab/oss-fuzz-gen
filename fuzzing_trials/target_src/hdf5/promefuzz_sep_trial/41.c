// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fis_hdf5 at H5Fdeprec.c:144:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fis_hdf5 at H5Fdeprec.c:144:1 in H5Fpublic.h
// H5Fis_hdf5 at H5Fdeprec.c:144:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "This is a dummy file for HDF5 testing.\n");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    // Prepare the environment
    write_dummy_file();

    // H5Fcreate -> H5Fclose -> H5Fclose -> H5Fis_hdf5 -> H5Fcreate -> H5Fclose -> H5Fis_hdf5 -> H5Fis_hdf5
    hid_t file_id;
    herr_t status;
    htri_t is_hdf5;

    // H5Fcreate
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // H5Fclose
    status = H5Fclose(file_id);
    
    // H5Fclose (again, should handle gracefully)
    status = H5Fclose(file_id);

    // H5Fis_hdf5
    is_hdf5 = H5Fis_hdf5("./dummy_file");

    // H5Fcreate
    file_id = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // H5Fclose
    status = H5Fclose(file_id);

    // H5Fis_hdf5
    is_hdf5 = H5Fis_hdf5("./dummy_file");

    // H5Fis_hdf5
    is_hdf5 = H5Fis_hdf5("./dummy_file");

    return 0;
}