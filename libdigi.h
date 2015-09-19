#include <stdio.h>
#include <stdlib.h>
#include <usb.h>

struct usb_dev_handle  *open_digispark(struct usb_device  *digiSpark);

struct usb_device *find_digispark();

int write_digispark(struct usb_dev_handle *handler, char thechar);

char  read_digispark(struct usb_dev_handle *handler);

int close_digispark(struct usb_dev_handle *handler,struct usb_device *digiSpark );
