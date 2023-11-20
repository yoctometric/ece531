
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
    int err;

    // request a read from the temperature sensor (TA register)
    uint8_t req_temp_msg = TA_ADDRESS;
    err = vmwos_i2c_write_blocking(DEVICE_ADDRESS, &req_temp_msg, 1);
    if (err != 0) {
        printf("    Error while writing to I2C: %d\n", err);
    }
    
    /*  response will be in form:
            [15]    [14]    [13]    [12]    [11-0]
            tavtc   tavtu   tavtl   sign    data (in twos compliment format)
    */

    uint8_t response[2] = {-1, -1};
    err = vmwos_i2c_read_blocking(DEVICE_ADDRESS, response, 2);

    if (err != 0) {
        printf("    Error while reading I2C results: %d\n", err);
    }

    // convert the response data into a temperature value.
    // see page 25 of https://cdn-shop.adafruit.com/datasheets/MCP9808.pdf

    // upper byte is response[0], lower byte is response[1]
    uint8_t ub = response[0] & 0x1f;    // clear out the flag bits
    uint8_t lb = response[1];
    int temperature;

    // calc temp based on the sign bit
    if ((ub & 0x10) == 0x10) {    // TA < 0 degrees c
        ub = ub & 0x0f;
        temperature = 256 - (ub * 16 + lb / 16);
    }
    else {
        temperature = ub * 16 + lb / 16;
    }

    printf("Read temperature from external sensor: %d degrees C\n", temperature);

    return 0;
}