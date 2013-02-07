#!/bin/zsh

if [ $# -lt 1 ]; then
    echo "Usage: `basename $0` sm1:machine1 [sm2:machine2 [...]]"
    exit 1
fi

for machine in "$@"; do
    sm=`echo $machine | cut -d':' -f1`
    name=`echo $machine | cut -d':' -f2-`
    if [ -f "macs/$sm.txt" ]; then
        line=`grep $name macs/$sm.txt | head -n1`    
        if [ -n $line ]; then
            mac=`echo $line | cut -d':' -f2- | tr -d ' '`
            echo -n "[$sm] $name : "
            wakeonlan $mac
        else
            echo "Unknown machine $machine."
        fi
    else
        echo "SM $sm has not been mapped yet."
    fi
done
