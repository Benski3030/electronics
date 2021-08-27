


Edit the crontab to 

`sudo crontab -e`

the add this line to the end of the file
`@reboot python3 /home/pi/Documents/orebox/ore_led.py`

Make sure the python file is executable by the system
`sudo chmod a+x /home/pi/Documents/orebox/ore_led.py`


