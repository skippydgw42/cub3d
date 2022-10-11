#!/bin/bash

i=0

while ./cub3D map/map.cub
do
	i=$((i + 1));
	echo "$i";
	clear;
done
