#include <linux/module.h>
#include <linux/random.h>
#include <linux/device.h> 
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/uaccess.h>

#define MAX 100000000
#define AUTHOR "Phan Xuan Bao<18120287>, Le Nguyen Tuan<18120631>, Pham Viet Xuan<18120658>"
#define DEVICE_NAME "RandomNumber"
#define MOD_DESC "Generative a random number. "
#define CLASS_NAME "RandNum"

static int majorNum;
static int timesOfOpens = 0;
static struct class* RandNum_class = NULL;
static struct device* RandDevice = NULL;


static int f_open(struct inode *inodep, struct file *filep){
	timesOfOpens++;
	printk(KERN_INFO "RandNum: Device has been opened %d time(s)\n", timesOfOpens);
	return 0;
}
static int f_release(struct inode *inodep, struct file *filep){
	printk(KERN_INFO "RandNum: Device successfully closed\n");
	return 0;
}
static ssize_t f_read(struct file *filep, char* usr_space, size_t len, loff_t* offset)
{
	int randNum;
	int error;
	get_random_bytes(&randNum, sizeof(randNum));
	randNum %= MAX;

	error = copy_to_user(usr_space, &randNum, sizeof(randNum));

	if (error == 0){
		printk(KERN_INFO "RandNum: Sent random number to the user\n");
		return 0;
	}
	else{
		printk(KERN_INFO "RandNum: Failed to send random number to the user\n");
		return -EFAULT;
	}
}

static struct file_operations f_ops = //file operand 
{
	.open = f_open,
	.release = f_release,
	.read = f_read,
};


static int __init init_random(void)//ham tao
{
    //dang ky mot major cho file thiet bi
    majorNum = register_chrdev(0, DEVICE_NAME, &f_ops);
    //neu that bai
    if (majorNum <0 )
    {
        //Xuat thong bao loi ra man hinh, return
        printk(KERN_INFO"RandNum: Register a major number failed");
        return majorNum;    
    }
    //neu thanh cong
    printk(KERN_INFO "RandNum: Register a major successfully. Major number is: %d", majorNum);

    //Tao mot device class co ten la DEVICE_NAME
    RandNum_class = class_create(THIS_MODULE,CLASS_NAME);

    if (IS_ERR(RandNum_class))
    {
        //Neu xay ra loi, unregister majorNum va return
        unregister_chrdev(majorNum,DEVICE_NAME);
        printk(KERN_ALERT"register device class failed!");
        return PTR_ERR(RandNum_class);
    }
    printk(KERN_INFO "RandNum: register device class successfuly.\n");
    //Dang ky mot device driver
    RandDevice = device_create(RandNum_class,NULL, MKDEV(majorNum,0), NULL, DEVICE_NAME);
    if (IS_ERR(RandDevice))
    {
        unregister_chrdev(majorNum,DEVICE_NAME);
        printk(KERN_ALERT "Register device driver failed!\n");
        return PTR_ERR(RandDevice);
    }
    printk(KERN_INFO "RandNum: Create device class correctly\n");
	return 0;
}


static void __exit exit_random(void)//ham huy
{
    // Xoa device
	device_destroy(RandNum_class, MKDEV(majorNum, 0)); 
	// huy register device class
	class_unregister(RandNum_class);
	// xoa device class
	class_destroy(RandNum_class);
	// unregister major number
	unregister_chrdev(majorNum, DEVICE_NAME);

    printk(KERN_INFO "RandNum: Unregistered random number.");
    return;
}

module_init(init_random);
module_exit(exit_random);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(MOD_DESC);
MODULE_VERSION("1");
