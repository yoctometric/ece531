
#include "drivers/i2c/i2c.h"
#include "drivers/bcm2835/bcm2835_io.h"
#include "lib/delay.h"

void i2c_init()
{
    // select the proper FSEL's for the i2c gpios
    bcm2835_write(GPIO_GPFSEL0, I2C_SDA_FSEL);
    bcm2835_write(GPIO_GPFSEL0, I2C_SCL_FSEL);

    // disable pupd for both pins
	bcm2835_write(GPIO_GPPUD, GPIO_GPPUD_DISABLE);
	delay(150);
	bcm2835_write(GPIO_GPPUDCLK0, (1 << I2C_SCL_PIN) | (1 << I2C_SDA_PIN));
	delay(150);
	bcm2835_write(GPIO_GPPUDCLK0, 0x0);

    // no need to define the i2c clock rate, the default value "should result in a 100kHz I2C clock frequency"
}


void i2c_write_blocking(uint8_t address, uint8_t *buf, size_t buflen)
{
    // set the address of the device
    bcm2835_write(REG_I2C_A, address);

    // clear the FIFO in case there was something in there left over
    bcm2835_write(REG_I2C_C, REGM_C_CLEAR);

    // reset the status register fields
    bcm2835_write(REG_I2C_S, REGM_S_DONE | REGM_S_CLKT | REGM_S_ERR);

    // set the data length 
    bcm2835_write(REG_I2C_DLEN, buflen);

    // tell the control register to start a write (simply do not set the READ bit)
    bcm2835_write(REG_I2C_C, REGM_C_I2CEN | REGM_C_ST);

    // put outgoing data onto the FIFO
    int i;
    for (i = 0; i < buflen; i++) {
        // wait for there to be space on the FIFO
        while(bcm2835_read(REG_I2C_S & REGM_S_TXD) == 0)
            asm("");

        // now that the fifo has space, pop on the next byte
        bcm2835_write(REG_I2C_FIFO, buf[i]);
    }
}


void i2c_read_blocking(uint8_t address, uint8_t *buf, size_t buflen)
{
    // set the address of the device
    bcm2835_write(REG_I2C_A, address);

    // clear the FIFO in case there was something in there left over
    bcm2835_write(REG_I2C_C, REGM_C_CLEAR);

    // reset the status register fields
    bcm2835_write(REG_I2C_S, REGM_S_DONE | REGM_S_CLKT | REGM_S_ERR);

    // set the data length 
    bcm2835_write(REG_I2C_DLEN, buflen);

    // tell the control register to start a read
    bcm2835_write(REG_I2C_C, REGM_C_I2CEN | REGM_C_ST | REGM_C_READ);

    // grab the incoming data off of the FIFO
    int i;
    for (i = 0; i < buflen; i++) {
        // wait for there to be something on the FIFO
        while(bcm2835_read(REG_I2C_S & REGM_S_RXD) == 0)
            asm("");

        // pop off of the fifo
        buf[i] = bcm2835_read(REG_I2C_FIFO);
    }
}