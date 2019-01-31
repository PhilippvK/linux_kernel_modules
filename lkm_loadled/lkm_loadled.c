#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/cpufreq.h> /* Needed for timers */
#include <linux/gpio.h> /* Needed for GPIO */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Philipp van Kempen");
MODULE_DESCRIPTION("A simple Linux Kernel Module indicating high CPU load by a LED.");
MODULE_VERSION("0.01");

#define PIN  21 // 40

#define THRESHOLD 85

MODULE_VERSION("0.01");
u64 prev_update_time;
u64 prev_idle_time;

char stop = 0;
const int g_time_interval = 10; // Interval: 10 ms = 0.01 second
struct timer_list g_timer;

void _TimerHandler(unsigned long data) {
  unsigned int io_busy, j, load, idle_time, time_elapsed;
  u64 cur_idle_time, update_time;
  /* Restarting the timer... */
  if (!stop) {
    mod_timer( &g_timer, jiffies + msecs_to_jiffies(g_time_interval));
  }
  j = 0;
  io_busy = 0; 
  cur_idle_time = get_cpu_idle_time(j, &update_time, io_busy);
  idle_time = cur_idle_time - prev_idle_time;
  time_elapsed = update_time - prev_update_time;
  if (time_elapsed < g_time_interval * 2 * 1000 ) {
    load = 100 * (time_elapsed - idle_time) / time_elapsed;
    //printk(KERN_INFO "LOAD=%d!\n",load);
    if (load > THRESHOLD) {
      gpio_set_value(PIN, 1);
    } else {
      gpio_set_value(PIN, 0);
    }
  }
  prev_idle_time = cur_idle_time;
  prev_update_time = update_time;
}

static int __init lkm_loadled_init(void) {
  printk(KERN_INFO "Init LOADLED!\n");
  gpio_request(PIN, "PIN");
  gpio_direction_output(PIN, 0);
  /* Starting the timer. */
  setup_timer(&g_timer, _TimerHandler, 0);
  mod_timer( &g_timer, jiffies + msecs_to_jiffies(g_time_interval));
  return 0;
}

static void __exit lkm_loadled_exit(void) {
  del_timer(&g_timer);
  stop = 1;
  gpio_set_value(PIN, 0);
  gpio_free(PIN);
  printk(KERN_INFO "Exit LOADLED!\n");
}

module_init(lkm_loadled_init);
module_exit(lkm_loadled_exit);
