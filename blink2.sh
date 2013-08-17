#!/bin/bash

LEDSTATUS=1

echo "1" > $LED


for (( i=1 ; i<=$1 ; i++))

do 

echo $LEDSTATUS

	if [ $LEDSTATUS == 1 ]; then 

   echo "0" > $LED
   LEDSTATUS=0

	else

   echo "1" > $LED
   LEDSTATUS=1

	fi

	sleep 1

done
