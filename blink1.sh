#!/bin/bash


for (( i=1 ; i<=$1 ; i++))

do 

   cat $SENS > $LED
   sleep 1
   cat $SENS > $LED
   sleep 1
done
