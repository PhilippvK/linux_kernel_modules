#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */

#include <linux/cpufreq.h> /* Needed for timers */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Philipp van Kempen");
MODULE_DESCRIPTION("A Linux Kernel Module printing a CPU stat.");
MODULE_VERSION("0.01");
u64 prev_update_time;
u64 prev_idle_time;

const int g_time_interval = 1000; // Interval: 1000 ms = 1 second
struct timer_list g_timer;

void _TimerHandler(unsigned long data) {
  unsigned int io_busy, j, load, idle_time, time_elapsed;
  u64 cur_idle_time, update_time;
  /* Restarting the timer... */
  mod_timer( &g_timer, jiffies + msecs_to_jiffies(g_time_interval));
  j = 0;
  io_busy = 0; 
  cur_idle_time = get_cpu_idle_time(j, &update_time, io_busy);
  idle_time = cur_idle_time - prev_idle_time;
  time_elapsed = update_time - prev_update_time;
  if (time_elapsed < g_time_interval * 2 * 1000 ) {
    load = 100 * (time_elapsed - idle_time) / time_elapsed;
    printk(KERN_INFO "LOAD=%d!\n",load);
  }
  prev_idle_time = cur_idle_time;
  prev_update_time = update_time;
}

static int __init lkm_example_init(void) {
  printk(KERN_INFO "Hello, World!\n");

  /* Starting the timer. */
  setup_timer(&g_timer, _TimerHandler, 0);
  mod_timer( &g_timer, jiffies + msecs_to_jiffies(g_time_interval));
  return 0;
}

static void __exit lkm_example_exit(void) {
  printk(KERN_INFO "Goodbye, World!\n");
  del_timer(&g_timer);
}

module_init(lkm_example_init);
module_exit(lkm_example_exit);
