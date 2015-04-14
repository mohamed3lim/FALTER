if [ "` lsmod | grep rtai_shm `" = "" ]; then
	echo inserting rtai shm module
	insmod /usr/realtime/modules/rtai_shm.ko
else
	echo rtai shm module already inserted
fi

if [ "` ls /tmp | grep usb `" = "" ]; then
	echo creating folder usb
	mkdir /tmp/usb
fi

if [ "` ls /dev | grep sdb1 `" != "" ]; then
	if [ "` mount | grep sdb1 `" = "" ]; then

		echo mounting usb-stick
		mount -o async /dev/sdb1 /tmp/usb
	else 
		echo usb stick already mounted	
	fi
else
	echo no usb stick found. 
	echo logs will be written to temporary file system.
fi

#starting the main program!
if [ $# -gt 0 ]; then
	if [ $1 == "p" ]; then
		./perception
	else
		./control
	fi
else
	./control
fi

sleep 1

echo Try to unmount /dev/sdb1
umount -f /tmp/usb
echo Umounting finished
