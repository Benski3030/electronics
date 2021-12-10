# Raspberry Pi Backup

## Overview
Here is a series of steps to make a backup (image) of you raspberry pi 


The process works like this:

1. Mount a USB drive to the pi
2. Image the OS to the USB drive
3. Compress and save the image using `pyshrink` 

Alternatively, step 3 could also happen on the pi itself, but it takes longer due to the limited compute power on the pi.

### Mount a USB

1. Start by updating your system with
    ```
    sudo apt update
    sudo apt upgrade
    ```

2. It helps if you install a plugin for `exFAT` so you can upload larger files to the usb.  Alternative you can use a native linux system to format a USB with `ext` as well.  `FAT` and `FAT32` *do not work* due to the 4GB file size limit.  

    ```
    sudo apt-get install exfat-fuse
    sudo apt-get install exfat-utils
    ```

3. create a mount point in the `/mnt` folder such as

    `sudo mkdir /mnt/backup`

4. Find the name of the drive with

    `sudo fdisk -l`

5. Then mount the drive with 

    `sudo mount /dev/sda1 /mnt/backup -o uid=pi,gid=pi`

6. The uid and gid options allow pi to read and write files on the USB key
And then check you can see your files and create a new one:

    ```
    ls -latr /mnt/backup
    touch /mnt/backup/test.txt
    ```

### Create an Image 

1. First, install *pyshrink* on the pi

    ```
    sudo wget https://raw.githubusercontent.com/Drewsif/PiShrink/master/pishrink.sh
    sudo chmod +x pishrink.sh
    sudo mv pishrink.sh /usr/local/bin
    ```
2. Check the mount point path of your USB drive by entering
   `lsblk`
3. You’ll see a list of drives connected to the Raspberry Pi and the mount point name of each. Your USB drive will probably be mounted at `/mnt/pi/[VOLUME NAME]`. In our case, it was `/mnt/backup`. If your drive isn’t mounted, try rebooting with the USB drive connected or you can mount it manually by typing sudo mkdir /dev/mysub to create a directory and sudo mount /dev/sda1 /dev/myusb to mount it. However, you can’t and shouldn’t do  that if it’s already mounted.
   
4. Copy all your data to an img file by using the dd command. 

    `sudo dd if=/dev/mmcblk0 of=[mount point]/myimg.img bs=1M`

    However, if you shrank a partition on the source microSD card, you’ll need to use the count attribute to tell it to copy only as many MBs as are in use. For example, in our case, we had had a 16GB card, but after shrinking the rootfs down to 6.5GB, the card only had about 6.8GB in use (when you count the /boot partition). So, to be on the safe side (better to copy too much data than too little), we rounded up and set dd to copy 7GB of data by using count=7000. The amount of data is equal to count * block size (bs) so 7000 * 1M means 7GB. 

    `sudo dd if=/dev/mmcblk0 of=[mount point]/myimg.img bs=1M count=7000`

5. Use pishrink with the -z parameter, which zips your image up with gzip

`sudo pishrink.sh -z myimg.img`

This process will also take several minutes but, when it is done, you will end up with a reasonably sized image file called myimg.img.gz. You can copy this file to your PC, upload it to the cloud or send it to a friend.  

6. Eject your usb drive with
    `sudo umount /mnt/backup` 
