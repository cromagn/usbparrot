#include "libdigi.h"
struct usb_dev_handle  *open_digispark(struct usb_device  *digiSpark)
{
    int result = 0;
    int numInterfaces = 0;
    struct usb_dev_handle *devHandle = NULL;
    struct usb_interface_descriptor *interface = NULL;


    devHandle = usb_open(digiSpark);

    if(devHandle != NULL)
    {
        result = usb_set_configuration(devHandle, digiSpark->config->bConfigurationValue);
        numInterfaces = digiSpark->config->bNumInterfaces;
        interface = &(digiSpark->config->interface[0].altsetting[0]);
        result = usb_claim_interface(devHandle, interface->bInterfaceNumber);

    }


    return devHandle;
}

struct usb_device *find_digispark()
{
    struct usb_bus *bus = NULL;
    struct usb_device *digiSpark = NULL;
    struct usb_device *device = NULL;

    // Initialize the USB library
    usb_init();
    //usb_set_debug(3);


    // Enumerate the USB device tree
    usb_find_busses();
    usb_find_devices();

    // Iterate through attached busses and devices
    bus = usb_get_busses();
    while(bus != NULL)
    {
        device = bus->devices;
        while(device != NULL)
        {
            // Check to see if each USB device matches the DigiSpark Vendor and Product IDs
            if((device->descriptor.idVendor == 0x16c0) && (device->descriptor.idProduct == 0x05df))
            {
                digiSpark = device;
                printf("--- Found Digispark device ---");
            }

            device = device->next;
        }

        bus = bus->next;
    }
    return digiSpark;
}
int write_digispark(struct usb_dev_handle *handler, char thechar)
{
    return usb_control_msg(handler, (0x01 << 5), 0x09, 0, thechar, 0, 0, 1000); //write
}

char  read_digispark(struct usb_dev_handle *handler)
{
    char thechar='-';
    usb_control_msg(handler, (0x01 << 5) | 0x80, 0x01, 0, 0, &thechar, 1, 1000);
    return thechar;
}

int close_digispark(struct usb_dev_handle *handler,struct usb_device *digiSpark )
{

    //int result=0;
    //struct usb_interface_descriptor *interface = NULL;
    //interface = &(digiSpark->config->interface[0].altsetting[0]);
    //result = usb_release_interface(handler, interface->bInterfaceNumber);
    //       if(result < 0) {printf("Error %i releasing Interface 0\n", result);return 1; }

    usb_close(handler);
    return 0;
}
