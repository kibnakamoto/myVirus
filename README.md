# This is a repository for multiple viruses

## 1.0 - virus\_del

the virus\_del folder has a c++ code and executable for deleting the everything it can without sudo rights.

The virus\_hog folder has the main virus. This virus hogs all your CPU power (multi-threading)
as well as all your memory and virtual memory in daemon processes. The only way to terminate this is
by restarting (or the system closes every running process because it cannot locate which process is
dangerous). it doesn't do any permenant damage but the file.
***hog\_add\_tosystem.sh*** is supposed to add to system and start virus upon booting and will
infect every folder with a shell file which will render your operating system useless (if it works, it will require a whole hard-drive format).
This folder is to be run on a bad usb with a physical attack. Will be tested with USB Rubber Ducky
by Hak5. 

The virus\_sto is a permenant virus for depleting your hard drive space by downloading gibberish
file names everywhere with gibberish content, it downloads around 100MB per file. It infects 1 existing file and 2 new (300MB per random path). It is completely unorginized and the folder paths to
damage are completly random which means you cannot group these files and delete them all at once,
you would need to delete one by one, except they are random and you cannot know where they are.

The purpose of making these viruses are only for educational purposes, they are not intented
for bad purposes. Licenced under the GPL 3.0 Licence
