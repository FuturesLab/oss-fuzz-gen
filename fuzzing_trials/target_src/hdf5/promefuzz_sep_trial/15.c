// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fmount at H5F.c:1183:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fmount at H5F.c:1183:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fmount at H5F.c:1183:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fmount at H5F.c:1183:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fmount at H5F.c:1183:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_obj_count at H5F.c:216:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_obj_count at H5F.c:216:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Funmount at H5F.c:1301:1 in H5Fpublic.h
// H5Funmount at H5F.c:1301:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "H5Fpublic.h"
#include "H5Ppublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        const char *data = "dummy data";
        fwrite(data, 1, strlen(data), file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    hid_t file_id1 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id1 >= 0) H5Fclose(file_id1);

    hid_t file_id2 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id2 >= 0) H5Fclose(file_id2);

    hid_t file_id3 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id3 >= 0) H5Fclose(file_id3);

    hid_t file_id4 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id4 >= 0) H5Fclose(file_id4);

    hid_t file_id5 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id5 >= 0) H5Fclose(file_id5);

    hid_t file_id6 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id6 >= 0) H5Fclose(file_id6);

    hid_t file_id7 = H5Fcreate("./dummy_file", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id7 >= 0) H5Fclose(file_id7);

    hid_t file_id8 = H5Fopen("./dummy_file", H5F_ACC_RDONLY, H5P_DEFAULT);
    hid_t file_id9 = H5Fopen("./dummy_file", H5F_ACC_RDONLY, H5P_DEFAULT);

    if (file_id8 >= 0 && file_id9 >= 0) {
        H5Fmount(file_id8, "/", file_id9, H5P_DEFAULT);
        H5Fclose(file_id8);
        H5Fclose(file_id9);
    }

    hid_t file_id10 = H5Fopen("./dummy_file", H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id10 >= 0) {
        H5Fmount(file_id10, "/", file_id10, H5P_DEFAULT);
        H5Fclose(file_id10);
    }

    hid_t file_id11 = H5Fopen("./dummy_file", H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id11 >= 0) {
        H5Fmount(file_id11, "/", file_id11, H5P_DEFAULT);
        H5Fclose(file_id11);
    }

    hid_t file_id12 = H5Fopen("./dummy_file", H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id12 >= 0) {
        H5Fmount(file_id12, "/", file_id12, H5P_DEFAULT);
        H5Fclose(file_id12);
    }

    hid_t file_id13 = H5Fopen("./dummy_file", H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id13 >= 0) {
        H5Fmount(file_id13, "/", file_id13, H5P_DEFAULT);
        H5Fclose(file_id13);
    }

    ssize_t obj_count1 = H5Fget_obj_count(file_id13, H5F_OBJ_ALL);
    H5Fclose(file_id13);

    ssize_t obj_count2 = H5Fget_obj_count(file_id13, H5F_OBJ_ALL);
    H5Fclose(file_id13);

    H5Funmount(file_id13, "/");
    H5Funmount(file_id13, "/");

    H5Fclose(file_id13);
    H5Fclose(file_id13);
    H5Fclose(file_id13);
    H5Fclose(file_id13);
    H5Fclose(file_id13);
    H5Fclose(file_id13);
    H5Fclose(file_id13);

    return 0;
}