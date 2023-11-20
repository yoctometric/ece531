#define __NR_blink	8192
#define __NR_setfont	8193
#define __NR_gradient		8194
#define __NR_tb1		8195
/* #define __NR_run		8196 obsolete */
/* #define __NR_stop		8197 obsolete */
#define __NR_temp		8198
#define __NR_random		8199
#define __NR_framebuffer_load	8200
#define __NR_malloc		8201


int vmwos_blink(int value);
int vmwos_tb1(void);
int vmwos_setfont(int which);
int vmwos_gradient(void);
int vmwos_get_temp(void);
int vmwos_random(uint32_t *buffer);
int vmwos_framebuffer_load(int x, int y, int depth, char *fb);
void *vmwos_malloc(uint32_t size);

/* willowec syscalls */
#define __NR_i2c_write  9101
#define __NR_i2c_read   9102
int vmwos_i2c_write_blocking(uint8_t address, uint8_t *buf, size_t buflen);
int vmwos_i2c_read_blocking(uint8_t address, uint8_t *buf, size_t buflen);
// no need to make a syscall for the i2c init because that is called by kernel_main