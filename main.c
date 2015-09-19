#include <stdio.h>
#include <stdlib.h>
#include <usb.h>
#include "libdigi.h"

int main (int argc, char **argv)
{

    int loop=0;
    int ret=0;
    struct usb_device *digiSpark = NULL;
    struct usb_dev_handle *devDSHandle = NULL;
    printf("--------------- find ---------------\n");
    digiSpark = find_digispark();
    printf("--------------- open ---------------\n");
    devDSHandle=open_digispark(digiSpark);
    printf("--------------- write ---------------\n");
    //ret=write_digispark(devDSHandle,'o');
    //ret=write_digispark(devDSHandle,'A');
    //ret=write_digispark(devDSHandle,'\n');

    for(loop=0; loop<20; loop++)
    {
        char readchar='0';
        ret=write_digispark(devDSHandle,'o');
        readchar=read_digispark(devDSHandle);
        printf("--------------- read  -->%c<--------------\n", readchar);

    }

    printf("--------------- close ---------------\n");
    close_digispark(devDSHandle,digiSpark);
    return 1;
}
