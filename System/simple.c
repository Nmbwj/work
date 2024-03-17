#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/jiffies.h>

/* This function is called when the module is loaded */
long unsigned int jafis, second;
int simple_init(void)
{
	printk(KERN_INFO "Loading Kernel Module Naol \n");
	printk(KERN_INFO "Golden ratio: %lu\n",GOLDEN_RATIO_PRIME);
	jafis = jiffies;
	printk(KERN_INFO "initial:: HZ:%d and jiffies:%lu\n",HZ,jafis);
	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	printk(KERN_INFO "Removing Kernel Module Naol\n");
	printk(KERN_INFO "gcd(3300, 24): %lu\n", gcd(3300,24));
	jafis -= jiffies;
	jafis *= -1;
	second = jafis / HZ;
	printk(KERN_INFO "number of inturrpt exit: %lu\n",jiffies);
	printk(KERN_INFO "The number of seconds laps between init and exit of module: %lu\n",second);
}

/* Macros for registering module entery exit points. */
module_init(simple_init);
module_exit(simple_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Naol");

