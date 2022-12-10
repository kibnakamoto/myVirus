#!/bin/sh
PATH_HOGSH=$(find ~ -name "virus_hog")
make clean && make && cd /; umask 0; nohup sh "$PATH_HOGSH/hog.sh" 0<&- &>/dev/null & # $( cd /; umask 0; setsid  ~/workspace/myVirus/virus_hog/hog.sh </dev/null &>/dev/null & )
