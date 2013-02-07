#!/bin/zsh

if [ $# -lt 1 ]; then
    echo "Usage: `basename $0` sm1:r01 [sm2:r02 [...]]"
    exit 1
fi

for arg in "$@"; do
    sm=`echo $arg | cut -d':' -f1`
    rangee=`echo $arg | cut -d':' -f2-`
    if [ -f "macs/$sm.txt" ]; then
        lines=`grep $rangee macs/$sm.txt`    
        if [ -n $lines ]; then
            echo $lines | while read line; do
                mac=`echo $line | cut -d':' -f2- | tr -d ' '`
                name=`echo $line | cut -d':' -f1 | tr -d ' '`
                echo -n "[$sm] $name : "
                wakeonlan $mac
            done
        else
            echo "Unknown row $arg."
        fi
    else
        echo "SM $sm has not been mapped yet."
    fi
done
