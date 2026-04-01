#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> // Include for struct timeval
#include "/src/libhtp/htp/htp.h"  // Correct path for the header where htp_connp_open is declared

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Initialize and allocate memory for htp_connp_t
    htp_connp_t *connp = htp_connp_create(NULL); // Use a function to create htp_connp_t instead of malloc
    if (connp == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Initialize strings for IP addresses
    const char *client_ip = "127.0.0.1";
    const char *server_ip = "192.168.1.1";

    // Define port numbers
    int client_port = 8080;
    int server_port = 80;

    // Initialize htp_time_t using struct timeval
    struct timeval current_time;
    current_time.tv_sec = 0;
    current_time.tv_usec = 0;

    // Call the function-under-test
    htp_connp_open(connp, client_ip, client_port, server_ip, server_port, &current_time);

    // Free allocated memory
    htp_connp_destroy_all(connp); // Use the appropriate function to free htp_connp_t

    return 0;
}