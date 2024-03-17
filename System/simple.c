#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

/* This function is called when the module is loaded */

int simple_init(void)
{
	printk(KERN_INFO "Loading Kernel Module Naol \n");
	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	printk(KERN_INFO "Removing Kernel Module Naol\n");

}

/* Macros for registering module entery exit points. */
module_init(simple_init);
module_exit(simple_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Naol");

