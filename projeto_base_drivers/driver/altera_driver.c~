#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Basic Driver PCIHello");
MODULE_AUTHOR("Marcos Olivera");

//-- Enums



//-- Hardware Handles

static void * hexport;  // handle to 32-bit output PIO
static void * inport;   // handle to 16-bit input PIO
static void * display;
static void * red_leds;
static void * green_leds;
static void * keys;
static void * switches;

//-- Char Driver Interface
static int   access_count =  0;
static int   MAJOR_NUMBER = 91;

static int     char_device_open    ( struct inode * , struct file *);
static int     char_device_release ( struct inode * , struct file *);
static ssize_t char_device_read    ( struct file * , char *,       size_t , loff_t *);
static ssize_t char_device_write   ( struct file * , const char *, size_t , loff_t *);

static struct file_operations file_opts = {
      .read = char_device_read,
      .open = char_device_open,
     .write = char_device_write,
   .release = char_device_release
};

static int char_device_open(struct inode *inodep, struct file *filep) {
   access_count++;
   printk(KERN_ALERT "altera_driver: opened %d time(s)\n", access_count);
   return 0;
}

static int char_device_release(struct inode *inodep, struct file *filep) {
   printk(KERN_ALERT "altera_driver: device closed.\n");
   return 0;
}

static ssize_t char_device_read(struct file *filep, char *buf, size_t len, loff_t *off) {
  short switches;
  size_t count = len;
  printk(KERN_ALERT "altera_driver: read %d bytes\n", len);
  
  while (len > 0) {
    switches = ioread16(inport);
    put_user(switches & 0xFF, buf++);
    put_user((switches >> 8) & 0xFF, buf++);
    len -= 2;
  }
  return count;
}

static ssize_t char_device_write(struct file *filep, const char *buf, size_t opt, loff_t *off) {
	//size_t count = len;
	//short b = 0;
	printk(KERN_ALERT "altera_driver: write %d bytes\n", sizeof(uint32_t));
	printk(KERN_ALERT "value inside buf %d\n",buf[len]);
	/*while (b <  len) {
	unsigned k = *((int *) ptr);
	ptr += 4;
	b   += 4;
	iowrite32(k, hexport);
	}*/
	//int meme = (int)buf[0];

	//(*hexport) = (void)meme;
	
	printk(KERN_ALERT "adress hexport pointer: %p \n" ,hexport);
	printk(KERN_ALERT "adress red_leds pointer: %p \n", red_leds);
	printk(KERN_ALERT "adress display pointer: %p \n",display);
	
	switch(opt){
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
	}
	
	//if(copy_from_user(hexport,buf,2*sizeof(uint32_t))) return -1;
	if(copy_from_user(display,buf,2*sizeof(uint32_t))) return -1;
	//if(copy_from_user(red_leds,buf,sizeof(uint32_t))) return -1;
	
	return sizeof(uint32_t);
}

//-- PCI Device Interface

static struct pci_device_id pci_ids[] = {
  { PCI_DEVICE(0x1172, 0x0004), },
  { 0, }
};

MODULE_DEVICE_TABLE(pci, pci_ids);

static int pci_probe(struct pci_dev *dev, const struct pci_device_id *id);
static void pci_remove(struct pci_dev *dev);

static struct pci_driver pci_driver = {
  .name     = "alterahello",
  .id_table = pci_ids,
  .probe    = pci_probe,
  .remove   = pci_remove,
};

static unsigned char pci_get_revision(struct pci_dev *dev) {
  u8 revision;

  pci_read_config_byte(dev, PCI_REVISION_ID, &revision);
  return revision;
}

static int pci_probe(struct pci_dev *dev, const struct pci_device_id *id) {
	int vendor;
	int retval;
	unsigned long resource;

	retval = pci_enable_device(dev);

	if (pci_get_revision(dev) != 0x01) {
	printk(KERN_ALERT "altera_driver: cannot find pci device\n");
	return -ENODEV;
	}

	pci_read_config_dword(dev, 0, &vendor);
	printk(KERN_ALERT "altera_driver: Found Vendor id: %x\n", vendor);

	resource = pci_resource_start(dev, 0);
	printk(KERN_ALERT "altera_driver: Resource start at bar 0: %lx\n", resource);

	hexport = ioremap_nocache(resource + 0xC000, 0x20);
	inport  = ioremap_nocache(resource + 0xC040, 0x20);
	display = ioremap_nocache(resource + 0xC080, 0x20);
	red_leds = ioremap_nocache(resource + 0xC100,0x20);
	green_leds = ioremap_nochache(resource + 0xC0C0,0x20);
	keys = ioremap_nocache(resource + 0xC140,0x20);
	switches = ioremap_nocache(resource + 0xC180,0x20);
	return 0;
}

static void pci_remove(struct pci_dev *dev) {
  iounmap(hexport);
  iounmap(inport);
  iounmap(display);
  iounmap(red_leds);
  iounmap(green_leds);
  iounmap(keys);
  iounmap(switches);
}


//-- Global module registration

static int __init altera_driver_init(void) {
   int t = register_chrdev(MAJOR_NUMBER, "de2i150_altera", &file_opts);
   t = t | pci_register_driver(&pci_driver);

   if(t<0)
      printk(KERN_ALERT "altera_driver: error: cannot register char or pci.\n");
   else
     printk(KERN_ALERT "altera_driver: char+pci drivers registered.\n");

   return t;
}

static void __exit altera_driver_exit(void) {
  printk(KERN_ALERT "Goodbye from de2i150_altera.\n");

  unregister_chrdev(MAJOR_NUMBER, "de2i150_altera");
  pci_unregister_driver(&pci_driver);
}

module_init(altera_driver_init);
module_exit(altera_driver_exit);
