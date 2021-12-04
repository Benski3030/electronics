## RetroPi 

#### Overview
Here are some basic and advanced setup options for installing RetroPie on a raspberry Pi 3 B/B+

## Safe Shutdown
Example for RetroPie:

1. Make sure internet connected.
2. Make sure keyboard connected.
3. Press F4 enter terminal.
4. In the terminal, type the one-line command below(Case sensitive):

`wget -O - "https://raw.githubusercontent.com/RetroFlag/retroflag-picase/master/install.sh" | sudo bash`

## Run ROMs from USB drive
Before proceeding, make sure the `usbromservice` (Optional packages section) is installed and enabled, especially if you have installed RetroPie manually.

1. Create a folder called `retropie-mount` on the USB drive
2. Plug into Raspberry Pi
3. It will proceed to automatically copy the RetroPie folder AND all of its contents (you may need to reboot to start the copying)

## Set shader for all 
1. Edit the retroarch.cfg file
2. `video_shader = "/opt/retropie/emulators/retroarch/shader/sharp-bilinear-simple"`
3. `video_shader_enable = "true"`