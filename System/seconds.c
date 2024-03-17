#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <linux/string.h>

#define BUFFER_SIZE 128
#define PROC_NAME "seconds"
long unsigned int jafis;
ssize_t proc_read(struct file *file, char __user *usr_buf,size_t count, loff_t *pos);

void reverse(char *s);
void itoa(long unsigned int n, char *);

static struct file_operations proc_ops = {
.owner = THIS_MODULE,
.read = proc_read,
};
/* This function is called when the module is loaded. */
int proc_init(void)
{
jafis = jiffies;
/* creates the /proc/hello entry */
proc_create(PROC_NAME, 0666, NULL,(void *) &proc_ops);
return 0;
}
/* This function is called when the module is removed. */
void proc_exit(void)
{
/* removes the /proc/hello entry */
remove_proc_entry(PROC_NAME, NULL);

}
/* This function is called each time /proc/hello is read */
ssize_t proc_read(struct file *file, char __user *usr_buf,
size_t count, loff_t *pos)
{
int rv = 0;
char buffer[BUFFER_SIZE];
static int completed = 0;
if (completed) {
completed = 0;
return 0;
}
completed = 1;

itoa(((jiffies-jafis)/HZ),buffer);
rv = (int) strlen(buffer);

/* copies kernel space buffer to user space usr buf */
copy_to_user(usr_buf, buffer, rv);
return rv;
}
void reverse(char *s)
{
	int c, i, j;
	for(i=0, j=strlen(s)-1; i<j; i++,j--)
	{
		c= *(s+i);
		*(s+i) = *(s+j);
		*(s+j) = c;
		
	}
}

void itoa(long unsigned int n, char *s)
{
	int i, sign;
	i = 0;
	*(s+i++) = '\n';
	do {
		*(s+i++) = n % 10 + '0';
	}while((n /=10) > 0);
	*(s+i) = '\0';
	reverse(s);
	
}
module_init(proc_init);
module_exit(proc_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Jiffies Module");
MODULE_AUTHOR("Naol");

