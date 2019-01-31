#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/gpio.h>

#include <linux/kthread.h>
#include <linux/delay.h>

//#include<linux/signal.h>
#include <linux/sched/signal.h>
//#include<asm/signal.h>
//#include<linux/wait.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Philipp van Kempen");
MODULE_DESCRIPTION("A simple Linux Kernel Module using GPIO.");
MODULE_VERSION("0.01");

#define PIN  21 // 40

#define THREAD_PRIORITY 45
#define THREAD_NAME "gpio"

struct task_struct *task;

int gpio_thread(void *data){
  // Allow the SIGKILL signal
  allow_signal(SIGKILL);

  while(!kthread_should_stop()) {
    gpio_set_value(PIN, 1);
    usleep_range(200000, 200000);
    gpio_set_value(PIN, 0);
    usleep_range(200000, 200000);
    if (signal_pending(task))
      break;
  }
  printk(KERN_INFO "Thread Stopping\n");
  do_exit(0);
  return 0;
 
}

void gpio_thread_init(void){
  printk(KERN_INFO "GPIO: starting thread...");
  task = kthread_run(gpio_thread, NULL, THREAD_NAME);
  if (task)
    printk(KERN_INFO "Thread Created successfully\n");
  else
    printk(KERN_ERR "Thread creation failed\n");
  printk(KERN_INFO "GPIO: starting thread done.");
}

void gpio_thread_exit(void){
  printk(KERN_INFO "GPIO: stopping thread...");
  if (task) {
    kthread_stop(task);
  }
  printk(KERN_INFO "GPIO: stopping thread done.");
}

static int __init lkm_gpio_init(void) {
  printk(KERN_INFO "Init GPIO!\n");
  gpio_request(PIN, "PIN");
  gpio_direction_output(PIN, 0);
  gpio_thread_init();
  return 0;
}

static void __exit lkm_gpio_exit(void) {
  gpio_thread_exit();
  gpio_set_value(PIN, 0);
  gpio_free(PIN);
  printk(KERN_INFO "Exit GPIO!\n");
}

module_init(lkm_gpio_init);
module_exit(lkm_gpio_exit);
