
#include "lib/i2c.h"
#include "drivers/bcm2835/bcm2835_io.h"


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

void i2c_write(uint8_t address, uint8_t *buf, size_t buflen)
{
    
}

void i2c_read(uint8_t address, uint8_t *buf, size_t buflen)
{

}