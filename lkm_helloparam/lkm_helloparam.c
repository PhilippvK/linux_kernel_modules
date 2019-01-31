#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Philipp van Kempen");
MODULE_DESCRIPTION("A simple example Linux module using parameters");
MODULE_VERSION("0.01");

static int count=1;
module_param(count,int,0660);

static char *name = "World";
module_param(name,charp,0660);


static int __init lkm_helloparam_init(void) {
  int i;
  for ( i = 0 ; i < count ; i++ ) {
    printk(KERN_INFO "Hello, %s!\n",name);
  }
  return 0;
}

static void __exit lkm_helloparam_exit(void) {
  printk(KERN_INFO "Goodbye, %s!\n",name);
}

module_init(lkm_helloparam_init);
module_exit(lkm_helloparam_exit);
