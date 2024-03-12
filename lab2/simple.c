#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

 int simple_init(void) {
    printk(KERN INFO "Loading Module\n"); return 0;
} 
void simple_exit(void) {
    printk(KERN INFO "Removing Module\n"); 
}
MODULE LICENSE("GPL"); 
MODULE DESCRIPTION("Simple Module"); 
MODULE AUTHOR("SGG"); 