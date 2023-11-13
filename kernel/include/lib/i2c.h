/*
Library for i2c communications on the RPI 3b+
Code by Willow Cunningham
*/

#include <stdint.h>
#include <stdlib.h>

#include "drivers/bcm2835/bcm2835_periph.h"

// see https://web.eece.maine.edu/~vweaver/classes/ece598_2015s/BCM2835-ARM-Peripherals.pdf page 30

// gpio pins for the i2c
#define I2C_SDA_PIN     2
#define I2C_SCL_PIN     3

#define I2C_SDA_FSEL    (4 << (I2C_SDA_PIN * 3)) // value to pass into the gpio fsel register to set i2c (alt func 0)
#define I2C_SCL_FSEL    (4 << (I2C_SDA_PIN * 3))

#define I2C_BASE        (IO_BASE + 0x00804000)

// registers for i2c
#define REG_I2C_C       (I2C_BASE + 0x0)
#define REG_I2C_S       (I2C_BASE + 0x4)
#define REG_I2C_DLEN    (I2C_BASE + 0x8)
#define REG_I2C_A       (I2C_BASE + 0xc)
#define REG_I2C_FIFO    (I2C_BASE + 0x10)
#define REG_I2C_DIV     (I2C_BASE + 0x14)
#define REG_I2C_DEL     (I2C_BASE + 0x18)
#define REG_I2C_CLKT    (I2C_BASE + 0x1c)

// masks for the i2c control register
#define REGM_C_I2CEN     (1 << 15)
#define REGM_C_INTR      (1 << 10)
#define REGM_C_INTT      (1 << 9)
#define REGM_C_INTD      (1 << 8)
#define REGM_C_ST        (1 << 7)
#define REGM_C_CLEAR     (3 << 4)
#define REGM_C_READ      (1 << 0)

// masks for the i2c status register
#define REGM_S_CLKT      (1 << 9)
#define REGM_S_ERR       (1 << 8)
#define REGM_S_RXF       (1 << 7)
#define REGM_S_TXE       (1 << 6)
#define REGM_S_RXD       (1 << 5)
#define REGM_S_TXD       (1 << 4)
#define REGM_S_RXR       (1 << 3)
#define REGM_S_TXW       (1 << 2)
#define REGM_S_DONE      (1 << 1)
#define REGM_S_TA        (1 << 0)


/*
    Sets up the gpio pins to be used for I2C
*/
void i2c_init();

/*
    writes <buflen> bytes from <buf> to the i2c device at <address>
*/
void i2c_write(uint8_t address, uint8_t *buf, size_t buflen);

/*
    reads <buflen> bytes into <buf> from the i2c device at <address>
*/
void i2c_read(uint8_t address, uint8_t *buf, size_t buflen);