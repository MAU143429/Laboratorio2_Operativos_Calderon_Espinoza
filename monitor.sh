#!/bin/bash


nice -n 20 python3 factorial.py &


pid=$!

sudo kill $pid


echo "Monitoreando proceso con PID $pid:"
top -p $pid -n 1
