# hog storage as daemon with multi-threading. make sure file locations are randomized to maximize annoyingness

while [ true ] ; do
	if [ -f hog ]; then
		./hog
	else
		sh run.sh
	fi
done

