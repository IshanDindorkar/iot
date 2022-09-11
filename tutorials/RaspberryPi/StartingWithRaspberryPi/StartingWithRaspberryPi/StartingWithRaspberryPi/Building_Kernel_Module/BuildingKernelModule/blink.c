#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <asm/io.h>


#define GPIO_BASE      0x3F200000
#define GPIO_BLOCK_SIZE     4096


// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

#define GPIO_SETB(g) GPIO_SET |= 1 <<(g)
#define GPIO_CLRB(g) GPIO_CLR |= 1 <<(g)


#define LED_PIN 21 // Maps to Pin 40 on the RasPi connector


volatile unsigned int * gpio;
struct timer_list led_timer;
int status = 0;

/* main function */
static void blink_timer(unsigned long ptr)
{
  printk("Toggling LED\n");
  if (status == 0) {
    GPIO_SETB(LED_PIN);
    status = 1;
  } else {
    GPIO_CLRB(LED_PIN);
    status = 0;
  }
  led_timer.expires = jiffies + HZ;
  add_timer(&led_timer);
}


static int blink_init(void)
{
  printk("Hello,LED world!\n");
  gpio = ioremap(GPIO_BASE,GPIO_BLOCK_SIZE);
  INP_GPIO(LED_PIN);
  OUT_GPIO(LED_PIN);
  init_timer(&led_timer);
  led_timer.function = blink_timer;
  led_timer.data = (unsigned long) status;
  led_timer.expires = jiffies + HZ;
  add_timer(&led_timer);
  return 0;
}

static void blink_exit(void)
{
  del_timer(&led_timer);
  GPIO_CLRB(LED_PIN);
  iounmap(gpio);
  printk("Good bye!\n");
}

module_init(blink_init);
module_exit(blink_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WWW");
MODULE_DESCRIPTION("LED Blinker Driver");
MODULE_VERSION("0.1");
