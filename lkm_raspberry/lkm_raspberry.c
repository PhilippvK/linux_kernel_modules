#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <soc/bcm2835/raspberrypi-firmware.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Philipp van Kempen");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

#define BUF_SIZE 8

static int __init lkm_example_init(void) {
  u32 val = 0;
  struct device_node firmware_node;
  struct rpi_firmware *firmware;
  struct {
    u32 id;
    u32 val;
  } data = {};
  int err;

  firmware = rpi_firmware_get(&firmware_node);
  err = rpi_firmware_property(firmware, RPI_FIRMWARE_GET_TEMPERATURE, &data, sizeof(data));
  //err = rpi_firmware_property(firmware, RPI_FIRMWARE_GET_MAX_TEMPERATURE, &data, sizeof(data));
  if (!err)
    val = data.val;
  printk(KERN_INFO "Hello, World!\n");
  printk(KERN_INFO "VAL=%d\n",val);
  printk(KERN_INFO "TEMP=%d.%d\n",val/1000,val%1000);
  return 0;
}

static void __exit lkm_example_exit(void) {
 printk(KERN_INFO "Goodbye, World!\n");
}

module_init(lkm_example_init);
module_exit(lkm_example_exit);
