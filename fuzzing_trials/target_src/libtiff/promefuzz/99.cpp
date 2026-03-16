// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFWarningExt at tif_warning.c:63:6 in tiffio.h
// TIFFErrorExt at tif_error.c:63:6 in tiffio.h
// TIFFError at tif_error.c:46:6 in tiffio.h
// TIFFErrorExtR at tif_error.c:107:6 in tiffio.h
// TIFFWarningExtR at tif_warning.c:80:6 in tiffio.h
// TIFFWarning at tif_warning.c:46:6 in tiffio.h
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdint>
#include <cstddef>
#include <tiffio.h>
#include <cstdarg>

static void fuzz_TIFFWarningExt(thandle_t handle, const uint8_t *Data, size_t Size) {
    if (Size < 3) return;
    const char *module = reinterpret_cast<const char*>(Data);
    const char *fmt = reinterpret_cast<const char*>(Data + 1);

    // Ensure null-termination to prevent buffer overflow
    std::string moduleStr(module, strnlen(module, Size - 1));
    std::string fmtStr(fmt, strnlen(fmt, Size - 1));

    // Validate format string
    if (!moduleStr.empty() && !fmtStr.empty() && fmtStr.find('%') == std::string::npos) {
        TIFFWarningExt(handle, moduleStr.c_str(), fmtStr.c_str());
    }
}

static void fuzz_TIFFErrorExt(thandle_t handle, const uint8_t *Data, size_t Size) {
    if (Size < 3) return;
    const char *module = reinterpret_cast<const char*>(Data);
    const char *fmt = reinterpret_cast<const char*>(Data + 1);

    // Ensure null-termination to prevent buffer overflow
    std::string moduleStr(module, strnlen(module, Size - 1));
    std::string fmtStr(fmt, strnlen(fmt, Size - 1));

    // Validate format string
    if (!moduleStr.empty() && !fmtStr.empty() && fmtStr.find('%') == std::string::npos) {
        TIFFErrorExt(handle, moduleStr.c_str(), fmtStr.c_str());
    }
}

static void fuzz_TIFFError(const uint8_t *Data, size_t Size) {
    if (Size < 3) return;
    const char *module = reinterpret_cast<const char*>(Data);
    const char *fmt = reinterpret_cast<const char*>(Data + 1);

    // Ensure null-termination to prevent buffer overflow
    std::string moduleStr(module, strnlen(module, Size - 1));
    std::string fmtStr(fmt, strnlen(fmt, Size - 1));

    // Validate format string
    if (!moduleStr.empty() && !fmtStr.empty() && fmtStr.find('%') == std::string::npos) {
        TIFFError(moduleStr.c_str(), fmtStr.c_str());
    }
}

static void fuzz_TIFFErrorExtR(TIFF *tif, const uint8_t *Data, size_t Size) {
    if (Size < 3) return;
    const char *module = reinterpret_cast<const char*>(Data);
    const char *fmt = reinterpret_cast<const char*>(Data + 1);

    // Ensure null-termination to prevent buffer overflow
    std::string moduleStr(module, strnlen(module, Size - 1));
    std::string fmtStr(fmt, strnlen(fmt, Size - 1));

    // Validate format string
    if (!moduleStr.empty() && !fmtStr.empty() && fmtStr.find('%') == std::string::npos) {
        TIFFErrorExtR(tif, moduleStr.c_str(), fmtStr.c_str());
    }
}

static void fuzz_TIFFWarningExtR(TIFF *tif, const uint8_t *Data, size_t Size) {
    if (Size < 3) return;
    const char *module = reinterpret_cast<const char*>(Data);
    const char *fmt = reinterpret_cast<const char*>(Data + 1);

    // Ensure null-termination to prevent buffer overflow
    std::string moduleStr(module, strnlen(module, Size - 1));
    std::string fmtStr(fmt, strnlen(fmt, Size - 1));

    // Validate format string
    if (!moduleStr.empty() && !fmtStr.empty() && fmtStr.find('%') == std::string::npos) {
        TIFFWarningExtR(tif, moduleStr.c_str(), fmtStr.c_str());
    }
}

static void fuzz_TIFFWarning(const uint8_t *Data, size_t Size) {
    if (Size < 3) return;
    const char *module = reinterpret_cast<const char*>(Data);
    const char *fmt = reinterpret_cast<const char*>(Data + 1);

    // Ensure null-termination to prevent buffer overflow
    std::string moduleStr(module, strnlen(module, Size - 1));
    std::string fmtStr(fmt, strnlen(fmt, Size - 1));

    // Validate format string
    if (!moduleStr.empty() && !fmtStr.empty() && fmtStr.find('%') == std::string::npos) {
        TIFFWarning(moduleStr.c_str(), fmtStr.c_str());
    }
}

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size) {
    thandle_t handle = nullptr;
    TIFF *tif = nullptr;

    fuzz_TIFFWarningExt(handle, Data, Size);
    fuzz_TIFFErrorExt(handle, Data, Size);
    fuzz_TIFFError(Data, Size);
    fuzz_TIFFErrorExtR(tif, Data, Size);
    fuzz_TIFFWarningExtR(tif, Data, Size);
    fuzz_TIFFWarning(Data, Size);

    return 0;
}