// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateTransform at cmsxform.c:1355:32 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsGetSupportedIntentsTHR at cmscnvrt.c:1157:27 in lcms2.h
// cmsGetSupportedIntentsTHR at cmscnvrt.c:1157:27 in lcms2.h
// cmsOpenProfileFromMem at cmsio0.c:1296:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateMultiprofileTransformTHR at cmsxform.c:1286:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsGetSupportedIntents at cmscnvrt.c:1192:27 in lcms2.h
// cmsGetSupportedIntents at cmscnvrt.c:1192:27 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateProofingTransformTHR at cmsxform.c:1366:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateExtendedTransform at cmsxform.c:1123:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static cmsHPROFILE createValidProfile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsHPROFILE)) return NULL;
    cmsHPROFILE profile = cmsOpenProfileFromMem(Data, Size);
    return profile;
}

static void fuzz_cmsGetSupportedIntents(void) {
    cmsUInt32Number intentCount = cmsGetSupportedIntents(0, NULL, NULL);

    cmsUInt32Number* codes = (cmsUInt32Number*)malloc(intentCount * sizeof(cmsUInt32Number));
    char** descriptions = (char**)malloc(intentCount * sizeof(char*));
    if (codes && descriptions) {
        cmsGetSupportedIntents(intentCount, codes, descriptions);

        // Assuming descriptions are allocated by the library and should not be freed by us
    }
    free(codes);
    free(descriptions);
}

static void fuzz_cmsCreateProofingTransformTHR(cmsContext ContextID, const uint8_t *Data, size_t Size) {
    if (Size < 3 * sizeof(cmsHPROFILE) + 5 * sizeof(cmsUInt32Number)) return;

    cmsHPROFILE Input = createValidProfile(Data, Size);
    cmsHPROFILE Output = createValidProfile(Data + sizeof(cmsHPROFILE), Size - sizeof(cmsHPROFILE));
    cmsHPROFILE Proofing = createValidProfile(Data + 2 * sizeof(cmsHPROFILE), Size - 2 * sizeof(cmsHPROFILE));
    if (!Input || !Output || !Proofing) {
        if (Input) cmsCloseProfile(Input);
        if (Output) cmsCloseProfile(Output);
        if (Proofing) cmsCloseProfile(Proofing);
        return;
    }

    cmsUInt32Number InputFormat = *(cmsUInt32Number*)(Data + 3 * sizeof(cmsHPROFILE));
    cmsUInt32Number OutputFormat = *(cmsUInt32Number*)(Data + 3 * sizeof(cmsHPROFILE) + sizeof(cmsUInt32Number));
    cmsUInt32Number Intent = *(cmsUInt32Number*)(Data + 3 * sizeof(cmsHPROFILE) + 2 * sizeof(cmsUInt32Number));
    cmsUInt32Number ProofingIntent = *(cmsUInt32Number*)(Data + 3 * sizeof(cmsHPROFILE) + 3 * sizeof(cmsUInt32Number));
    cmsUInt32Number dwFlags = *(cmsUInt32Number*)(Data + 3 * sizeof(cmsHPROFILE) + 4 * sizeof(cmsUInt32Number));

    cmsHTRANSFORM transform = cmsCreateProofingTransformTHR(ContextID, Input, InputFormat, Output, OutputFormat, Proofing, Intent, ProofingIntent, dwFlags);
    if (transform) {
        cmsDeleteTransform(transform);
    }

    cmsCloseProfile(Input);
    cmsCloseProfile(Output);
    cmsCloseProfile(Proofing);
}

static void fuzz_cmsCreateExtendedTransform(cmsContext ContextID, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) + 2 * sizeof(cmsHPROFILE) + sizeof(cmsUInt32Number) * 3) return;

    cmsUInt32Number nProfiles = *(cmsUInt32Number*)Data;
    if (nProfiles < 1 || nProfiles > 255) return;

    size_t requiredSize = sizeof(cmsUInt32Number) + nProfiles * (sizeof(cmsHPROFILE) + sizeof(cmsUInt32Number) + sizeof(cmsFloat64Number)) + 3 * sizeof(cmsUInt32Number);
    if (Size < requiredSize) return;

    cmsHPROFILE* hProfiles = (cmsHPROFILE*)malloc(nProfiles * sizeof(cmsHPROFILE));
    if (!hProfiles) return;

    for (cmsUInt32Number i = 0; i < nProfiles; i++) {
        hProfiles[i] = createValidProfile(Data + sizeof(cmsUInt32Number) + i * sizeof(cmsHPROFILE), Size - (sizeof(cmsUInt32Number) + i * sizeof(cmsHPROFILE)));
        if (!hProfiles[i]) {
            for (cmsUInt32Number j = 0; j < i; j++) {
                cmsCloseProfile(hProfiles[j]);
            }
            free(hProfiles);
            return;
        }
    }

    cmsUInt32Number* Intents = (cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + nProfiles * sizeof(cmsHPROFILE));
    cmsFloat64Number* AdaptationStates = (cmsFloat64Number*)(Data + sizeof(cmsUInt32Number) + nProfiles * (sizeof(cmsHPROFILE) + sizeof(cmsUInt32Number)));
    cmsUInt32Number InputFormat = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + nProfiles * (sizeof(cmsHPROFILE) + sizeof(cmsUInt32Number) + sizeof(cmsFloat64Number)));
    cmsUInt32Number OutputFormat = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + nProfiles * (sizeof(cmsHPROFILE) + sizeof(cmsUInt32Number) + sizeof(cmsFloat64Number)) + sizeof(cmsUInt32Number));
    cmsUInt32Number dwFlags = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + nProfiles * (sizeof(cmsHPROFILE) + sizeof(cmsUInt32Number) + sizeof(cmsFloat64Number)) + 2 * sizeof(cmsUInt32Number));

    cmsHTRANSFORM transform = cmsCreateExtendedTransform(ContextID, nProfiles, hProfiles, NULL, Intents, AdaptationStates, NULL, 0, InputFormat, OutputFormat, dwFlags);
    if (transform) {
        cmsDeleteTransform(transform);
    }

    for (cmsUInt32Number i = 0; i < nProfiles; i++) {
        cmsCloseProfile(hProfiles[i]);
    }
    free(hProfiles);
}

static void fuzz_cmsCreateTransform(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(cmsHPROFILE) + 4 * sizeof(cmsUInt32Number)) return;

    cmsHPROFILE Input = createValidProfile(Data, Size);
    cmsHPROFILE Output = createValidProfile(Data + sizeof(cmsHPROFILE), Size - sizeof(cmsHPROFILE));
    if (!Input || !Output) {
        if (Input) cmsCloseProfile(Input);
        if (Output) cmsCloseProfile(Output);
        return;
    }

    cmsUInt32Number InputFormat = *(cmsUInt32Number*)(Data + 2 * sizeof(cmsHPROFILE));
    cmsUInt32Number OutputFormat = *(cmsUInt32Number*)(Data + 2 * sizeof(cmsHPROFILE) + sizeof(cmsUInt32Number));
    cmsUInt32Number Intent = *(cmsUInt32Number*)(Data + 2 * sizeof(cmsHPROFILE) + 2 * sizeof(cmsUInt32Number));
    cmsUInt32Number dwFlags = *(cmsUInt32Number*)(Data + 2 * sizeof(cmsHPROFILE) + 3 * sizeof(cmsUInt32Number));

    cmsHTRANSFORM transform = cmsCreateTransform(Input, InputFormat, Output, OutputFormat, Intent, dwFlags);
    if (transform) {
        cmsDeleteTransform(transform);
    }

    cmsCloseProfile(Input);
    cmsCloseProfile(Output);
}

static void fuzz_cmsGetSupportedIntentsTHR(cmsContext ContextID) {
    cmsUInt32Number intentCount = cmsGetSupportedIntentsTHR(ContextID, 0, NULL, NULL);

    cmsUInt32Number* codes = (cmsUInt32Number*)malloc(intentCount * sizeof(cmsUInt32Number));
    char** descriptions = (char**)malloc(intentCount * sizeof(char*));
    if (codes && descriptions) {
        cmsGetSupportedIntentsTHR(ContextID, intentCount, codes, descriptions);

        // Assuming descriptions are allocated by the library and should not be freed by us
    }
    free(codes);
    free(descriptions);
}

static void fuzz_cmsCreateMultiprofileTransformTHR(cmsContext ContextID, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) + 2 * sizeof(cmsHPROFILE) + 4 * sizeof(cmsUInt32Number)) return;

    cmsUInt32Number nProfiles = *(cmsUInt32Number*)Data;
    if (nProfiles < 1 || nProfiles > 255) return;

    size_t requiredSize = sizeof(cmsUInt32Number) + nProfiles * sizeof(cmsHPROFILE) + 3 * sizeof(cmsUInt32Number);
    if (Size < requiredSize) return;

    cmsHPROFILE* hProfiles = (cmsHPROFILE*)malloc(nProfiles * sizeof(cmsHPROFILE));
    if (!hProfiles) return;

    for (cmsUInt32Number i = 0; i < nProfiles; i++) {
        hProfiles[i] = createValidProfile(Data + sizeof(cmsUInt32Number) + i * sizeof(cmsHPROFILE), Size - (sizeof(cmsUInt32Number) + i * sizeof(cmsHPROFILE)));
        if (!hProfiles[i]) {
            for (cmsUInt32Number j = 0; j < i; j++) {
                cmsCloseProfile(hProfiles[j]);
            }
            free(hProfiles);
            return;
        }
    }

    cmsUInt32Number InputFormat = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + nProfiles * sizeof(cmsHPROFILE));
    cmsUInt32Number OutputFormat = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + nProfiles * sizeof(cmsHPROFILE) + sizeof(cmsUInt32Number));
    cmsUInt32Number Intent = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + nProfiles * sizeof(cmsHPROFILE) + 2 * sizeof(cmsUInt32Number));
    cmsUInt32Number dwFlags = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + nProfiles * sizeof(cmsHPROFILE) + 3 * sizeof(cmsUInt32Number));

    cmsHTRANSFORM transform = cmsCreateMultiprofileTransformTHR(ContextID, hProfiles, nProfiles, InputFormat, OutputFormat, Intent, dwFlags);
    if (transform) {
        cmsDeleteTransform(transform);
    }

    for (cmsUInt32Number i = 0; i < nProfiles; i++) {
        cmsCloseProfile(hProfiles[i]);
    }
    free(hProfiles);
}

int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size) {
    cmsContext ContextID = NULL; // Assuming a default context

    fuzz_cmsGetSupportedIntents();
    fuzz_cmsCreateProofingTransformTHR(ContextID, Data, Size);
    fuzz_cmsCreateExtendedTransform(ContextID, Data, Size);
    fuzz_cmsCreateTransform(Data, Size);
    fuzz_cmsGetSupportedIntentsTHR(ContextID);
    fuzz_cmsCreateMultiprofileTransformTHR(ContextID, Data, Size);

    return 0;
}