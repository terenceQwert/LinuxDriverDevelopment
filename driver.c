#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>

#include <linux/sched.h>
#include <asm/current.h>

#include <linux/fs.h>
#include <linux/uaccess.h>
MODULE_DESCRIPTION("Hello World from Linux driver!!");/* 此程式介紹與描述*/
MODULE_AUTHOR("Terence_Liu@phoenix.com ");/* 此程式作者*/
MODULE_LICENSE("GPL");/* 程式 License*/

static const char    g_s_Hello_World_string[] = "Hello world from kernel mode!\n\0";
static const ssize_t g_s_Hello_World_size = sizeof(g_s_Hello_World_string);
static ssize_t device_file_read(
                        struct file *file_ptr
                       , char __user *user_buffer
                       , size_t count
                       , loff_t *position)
{
    printk( KERN_NOTICE "Simple-driver: Device file is read at offset = %i, read bytes count = %u\n"
                , (int)*position
                , (unsigned int)count );
    /* If position is behind the end of a file we have nothing to read */
    if( *position >= g_s_Hello_World_size )
        return 0;
    /* If a user tries to read more than we have, read only as many bytes as we have */
    if( *position + count > g_s_Hello_World_size )
        count = g_s_Hello_World_size - *position;
    if( copy_to_user(user_buffer, g_s_Hello_World_string + *position, count) != 0 )
        return -EFAULT;    
    /* Move reading position */
    *position += count;
    return count;
} // It was originally published on https://www.apriorit.com/

static struct file_operations simple_driver_fops = {
  .owner = THIS_MODULE,
  .read = device_file_read,
};

static int device_file_major_number = 0;
static const char device_name [] = "LinuxDriverSample";



/*
*  a global variale to record a new created node...
*/
dev_t devid;
/*
* a named object for dynamic test, and its default conut number for unregister_xxx
*/
char DynamicName[] = "Sample";
#define NEWCHRLED_CNT 1


/*
* add a sample init variable as initialized function argument
*/
static unsigned int devnode_major = 0;

/*
* define a standard fops structure & object
*/
static int hello_fops1_open(struct inode *inode, struct file *file)
{
    printk("open_hello1!!!\n");
    return 0;
}

static struct file_operations hello1_fops={
  .owner=THIS_MODULE,
  .open =hello_fops1_open,
  .read = device_file_read,
};

static struct cdev hello1_cdev;

/*
* 
*/
static int devnode_init(void)
{
  printk("devnode_init entry\n");
  int major = 1, minor;
  if( major)
  {
//    register_chrdev_region(devid, 1, DynamicName);
//    devid = MKDEV(major, 0);
    alloc_chrdev_region(&devid, 0,4, DynamicName);
    major = MAJOR(devid);
    cdev_init( &hello1_cdev, &hello1_fops);
    cdev_add( &hello1_cdev, MKDEV(major,0),2);
    printk("<1.1>Sample devid=%d\n", devid);

    return 0;
  } else 
  {
    alloc_chrdev_region(&devid, 0, 1, DynamicName);
    major = MAJOR(devid);
    minor = MINOR(devid);
    printk("<1.2>Sample devid=%d\n", devid);
    return 0;
  }
  return -1;
}


static void devnode_del(void)
{
#if 0
  unregister_chrdev(devid, DynamicName);
#else
  //
  // by using dynamic, and to remove device, must use unregister_chrdev_region to exercise,
  // otherwiese, this node can still be seen by command cat /proc/device 
  //
  unregister_chrdev_region(devid, NEWCHRLED_CNT);
#endif
}
int register_device(void)
{
    int result = 0;
    printk("<1> LinuxDriverSample: register_device\n ");
    printk( KERN_NOTICE "Simple-driver: register_device() is called.\n" );
    result = register_chrdev( 0, device_name, &simple_driver_fops );
    if( result < 0 )
    {
      printk( KERN_WARNING "Simple-driver:  can\'t register character device with error code = %i\n", result );
      return result;
    }
    device_file_major_number = result;
    printk( KERN_NOTICE "Simple-driver: registered character device with major number = %i and minor numbers 0...255\n", device_file_major_number );
    return 0;
} // It was originally published on https://www.apriorit.com/

void unregister_device(void)
{
    printk( KERN_NOTICE "Simple-driver: unregister_device() is called\n" );
    if(device_file_major_number != 0)
    {
        unregister_chrdev(device_file_major_number, device_name);
    }
} //It was originally published on https://www.apriorit.com/



static int my_init(void)
{
  printk("simple driver init\n");
  printk("parameter devnode_major = %u\n", devnode_major);
#if 0
  register_device();
#else
  //
  //  Use dynamic allocate method to create device node
  //
  devnode_init();
#endif
  return 0;
}

static void my_exit(void)
{
  printk("sample driver exit\n");
  devnode_del();
  return;
}



module_init(my_init);
module_exit(my_exit);

module_param( devnode_major, uint, 0);
MODULE_LICENSE("GPL");
