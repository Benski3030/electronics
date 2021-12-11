# Mount a USB on a Raspberry Pi

## Overview
Sometimes it is helpful to have a mounted USB drive connected to the pi.  There are several reasons for this, including;
* keep data separate from the OS (USB rom mount for RetroPie)
* backups and logging 
* hosting remote apps
* data transfer

There are two options for this task: one, ad-hoc mount on-demand, and two, the mount persists and activates whenever the pi is turned on.

### Ad-hoc mount

1. Display all disks and find you USB drive
   `sudo fdisk -l`

    Not the following:
    * The filesystem format type: here it’s FAT32, it could be NTFS or EXT4 for example
    * The device name: here it’s `/dev/sda1`
2. Display the UUID for the drive
   
   `sudo ls -l /dev/disk/by-uuid/`.

   Find the line corresponding to your drive name (sda1 for example)
    Note the UUID just before the drive name (it could be longer depending on your disk)
3. Create the mount directory
   
   `sudo mkdir /mnt/usb`
4. Mount the USB drive
   
   `sudo mount /dev/sda1 /mnt/usb -o uid=pi,gid=pi`

5. Verify the drive

    `ls -latr /mnt/usb`

6. Remove the USB when finished

    `sudo umount /mnt/usb`

#### Automate the process

1. Create a new file
2. 
    `sudo nano /usr/local/bin/usb-connect.sh`

    Paste these lines:

    ```
    #!/bin/bash
    sudo mount /dev/sda1 /mnt/usb -o uid=pi,gid=pi echo "USB drive mounted successfully"
    ```

    This is a basic script, adapt the values and add what you want
    Save and exit (CTRL+O, CTRL+X)
    Add execution permission:
    
    `sudo chmod +x /usr/local/bin/usb-connect.sh`

3. Create an alias

Edit your .bashrc file
    
    `nano ~/.bashrc`
Add this line at the end of the file
    
    `alias usbmount='/usr/local/bin/usb-connect.sh'`
    
Close the terminal or end your SSH connection.  

4. The next time you plug in your usb, just enter the following command in the terminal

`usbmount`

### Automatically mount the USB drive

1. Open /etc/fstab

    `sudo nano /etc/fstab`

2. Add the following line of code to the end
    `UUID=2014-3D52 /mnt/usb vfat uid=pi,gid=pi 0 0`

3. Save, exit, and reoboot the pi

The USB drive will be available in the selected folder. 

