#!/bin/bash
FILE=$1
NUM=$2
if [ $# -eq 0 ]; # проверяем количесто аргументов на ноль
then
	echo "whats filename?: " # спрашиваем название файла, если аргументы не даны
	read FILE
fi
if [ $FILE = "?" ]; # проверяем если задали вопрос и выводим подсказку
then
	echo "usage: lab21.bash filename length"
	exit
fi
if [ $# -le 1 ]; # если аргументов недодали, то спрашиавем длину
then
	echo "whats length?: "
	read NUM
fi
LEN=`wc -c $FILE` # узнаем длину файла в байтах
LEN=${LEN%% *} # выделяем из wc нужную часть
CNT=`expr $NUM / $LEN` # целочисленно делим
for (( i=0; i < $CNT; i++ ))  do # выводим столько раз склько надо
	cat $FILE
done
