
#include <stddef.h>
#include <stdint.h>

#ifdef VMWOS
#include "syscalls.h"
#include "vlibc.h"
#include "vmwos.h"
#else
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#endif

#define DEVICE_ADDRESS  0x18    // assuming a2, a1, a0 are set to 0
#define TA_ADDRESS  0x5

int main(int argc, char **argv) {
    printf("Temperature time....\n");

    // temperature default config may be sufficient

    // request a read from the temperature sensor (TA register)
    uint8_t req_temp_msg = TA_ADDRESS;
    vmwos_i2c_write_blocking(DEVICE_ADDRESS, &req_temp_msg, 1);
    /*  response will be in form:
            [15]    [14]    [13]    [12]    [11-0]
            tavtc   tavtu   tavtl   sign    data (in twos compliment format)
    */

    uint8_t response[2] = {0, 0};
    vmwos_i2c_read_blocking(DEVICE_ADDRESS, response, 2);

    printf("    response: %x, %x\n", response[1], response[0]);

    return 0;
}