#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static void fuzz_cmsOpenProfileFromStream(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    file = fopen("./dummy_file", "rb");
    if (!file) {
        return;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of cmsOpenProfileFromStream
    cmsHPROFILE profile = cmsOpenProfileFromStream(file, (const char *)"w");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (profile) {
        cmsCloseProfile(profile);
    }
    // Remove the fclose here to prevent double-free.
    // fclose(file);
}

static void fuzz_cmsCreateDeviceLinkFromCubeFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    cmsHPROFILE profile = cmsCreateDeviceLinkFromCubeFile("./dummy_file");
    if (profile) {
        cmsCloseProfile(profile);
    }
}

static void fuzz_cmsOpenProfileFromIOhandler2THR(const uint8_t *Data, size_t Size) {
    cmsContext context = NULL;
    cmsIOHANDLER *ioHandler = cmsOpenIOhandlerFromFile(context, "./dummy_file", "rb");
    if (!ioHandler) {
        return;
    }

    cmsHPROFILE profile = cmsOpenProfileFromIOhandler2THR(context, ioHandler, FALSE);
    if (profile) {
        cmsCloseProfile(profile);
    }
    cmsCloseIOhandler(ioHandler);
}

static void fuzz_cmsCreateDeviceLinkFromCubeFileTHR(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    cmsContext context = NULL;
    cmsHPROFILE profile = cmsCreateDeviceLinkFromCubeFileTHR(context, "./dummy_file");
    if (profile) {
        cmsCloseProfile(profile);
    }
}

static void fuzz_cmsOpenProfileFromFileTHR(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    cmsContext context = NULL;
    cmsHPROFILE profile = cmsOpenProfileFromFileTHR(context, "./dummy_file", "r");
    if (profile) {
        cmsCloseProfile(profile);
    }
}

static void fuzz_cmsOpenIOhandlerFromFile(const uint8_t *Data, size_t Size) {
    cmsContext context = NULL;
    cmsIOHANDLER *ioHandler = cmsOpenIOhandlerFromFile(context, "./dummy_file", "rb");
    if (ioHandler) {
        cmsCloseIOhandler(ioHandler);
    }
}

int LLVMFuzzerTestOneInput_133(const uint8_t *Data, size_t Size) {
    fuzz_cmsOpenProfileFromStream(Data, Size);
    fuzz_cmsCreateDeviceLinkFromCubeFile(Data, Size);
    fuzz_cmsOpenProfileFromIOhandler2THR(Data, Size);
    fuzz_cmsCreateDeviceLinkFromCubeFileTHR(Data, Size);
    fuzz_cmsOpenProfileFromFileTHR(Data, Size);
    fuzz_cmsOpenIOhandlerFromFile(Data, Size);
    return 0;
}