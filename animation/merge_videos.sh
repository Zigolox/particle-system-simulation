#!/usr/bin/bash

string=""
cpus=4
for ((i=0;i<cpus;i++))
do
  filename="../videos/${i}$1"
  ffmpeg -i "${filename}.mp4" -c copy -bsf:v h264_mp4toannexb -f mpegts -loglevel fatal "${filename}.ts"
  string="${string}|${filename}.ts"
done
string=${string:1:${#string}-1}

ffmpeg -i "concat:${string}" -c copy -loglevel fatal -bsf:a aac_adtstoasc "../videos/$1.mp4"

for ((i=0;i<cpus;i++))
do
  filename="../videos/${i}$1"
  rm "${filename}.ts"
  rm "${filename}.mp4"
done

# string=""
# for i in {0..3}
# do
#   filename="${i}test_animation"
#   string="${string}|${filename}.ts"
# done
#
#
# echo $string
