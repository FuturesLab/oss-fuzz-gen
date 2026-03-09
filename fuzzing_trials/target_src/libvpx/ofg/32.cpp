extern "C" {
    #include <vpx/vpx_decoder.h>
    #include <vpx/vp8dx.h>
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // Early exit if there's no data to process
    }

    // Call the function-under-test
    vpx_codec_iface_t *iface = vpx_codec_vp9_dx();

    // Initialize codec context
    vpx_codec_ctx_t codec;
    vpx_codec_err_t res;
    
    // Initialize the codec
    res = vpx_codec_dec_init(&codec, iface, NULL, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Decode the input data
    res = vpx_codec_decode(&codec, data, size, NULL, 0);
    if (res != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec);
        return 0;
    }

    // Retrieve the decoded frame
    vpx_codec_iter_t iter = NULL;
    vpx_image_t *img = NULL;
    while ((img = vpx_codec_get_frame(&codec, &iter)) != NULL) {
        // Process the image (if needed)
        // For example, access img->d_w, img->d_h, img->fmt, etc.

        // Add additional processing to ensure the image is being utilized
        // This could involve checking image properties or performing operations
        if (img->d_w > 0 && img->d_h > 0) {
            // Example: Access some pixel data
            unsigned int pixel_count = img->d_w * img->d_h;
            for (unsigned int i = 0; i < pixel_count; ++i) {
                // Access pixel data (depending on img->fmt)
                // This is just an example and may need to be adapted based on actual format
                unsigned char *pixel = img->planes[0] + i;
                // Perform a simple operation on the pixel to ensure it's being processed
                *pixel = ~(*pixel); // Invert the pixel value
            }
        }
    }

    // Destroy the codec context
    vpx_codec_destroy(&codec);

    return 0;
}