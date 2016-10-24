#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");

int init_module(void);

void cleanup_module(void);

static ssize_t dev_first_write(struct file *filp, const char *buffer, size_t length, loff_t *offset);

static ssize_t dev_second_write(struct file *filp, const char *buffer, size_t length, loff_t *offset);

static ssize_t dev_operator_write(struct file *filp, const char *buffer, size_t length, loff_t *offset);

static ssize_t proc_read(struct file *filp, char *buffer, size_t length, loff_t *offset);


#define BUF_LEN 80

static int major_operand_1;
static int major_operand_2;
static int major_operator;

static char result[BUF_LEN];
static char first[BUF_LEN];
static char second[BUF_LEN];
static char operand[BUF_LEN];


static struct file_operations fops = {
        .owner = THIS_MODULE,
        .read = proc_read
};

static struct file_operations dev_first_fops = {
        .owner = THIS_MODULE,
        .write = dev_first_write,
};

static struct file_operations dev_second_fops = {
        .owner = THIS_MODULE,
        .write = dev_second_write
};

static struct file_operations dev_operator_fops = {
        .owner = THIS_MODULE,
        .write = dev_operator_write
};

static struct proc_dir_entry *proc_result;

static ssize_t dev_first_write(struct file *filp, const char *buff, size_t len, loff_t *off) {
    if (copy_from_user(first, buff, len)) {
        return -EFAULT;
    }
    return len;
}

static ssize_t dev_second_write(struct file *filp, const char *buff, size_t len, loff_t *off) {
    if (copy_from_user(second, buff, len)) {
        return -EFAULT;
    }
    return len;
}

static ssize_t dev_operator_write(struct file *filp, const char *buff, size_t len, loff_t *off) {
    if (copy_from_user(operand, buff, len)) {
        return -EFAULT;
    }
    return len;
}
