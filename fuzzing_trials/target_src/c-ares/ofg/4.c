#include <ares.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <netinet/in.h> // For AF_INET
#include <netdb.h> // For struct hostent

// Callback function declaration
void callback_func(void *arg, int status, int timeouts, struct hostent *host) {
    /* Callback implementation (can be empty for fuzzing purposes) */
}

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    /* Declare and initialize variables */
    ares_channel channel;
    struct ares_options options;
    memset(&options, 0, sizeof(options));
    options.flags = ARES_FLAG_NOCHECKRESP; // Example option
    const char *servers[] = {"8.8.8.8"}; // Example DNS server
    options.servers = servers[0]; // Assign the first server
    options.nservers = 1;

    /* Initialize the ares channel */
    int status = ares_init_options(&channel, &options, sizeof(options));
    if (status != ARES_SUCCESS) {
        return 0; // Initialization failed
    }

    /* Prepare the address and its length */
    const void *addr = data; // Use the input data as the address
    int addrlen = (int)size; // Use the size of the data as the address length
    int family = AF_INET; // Use IPv4 for this example

    /* Call the function under test */
    ares_gethostbyaddr(channel, addr, addrlen, family, callback_func, NULL);

    /* Clean up the ares channel */
    ares_destroy(channel);
    return 0;
}