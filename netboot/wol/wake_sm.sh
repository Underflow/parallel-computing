#!/bin/zsh

if [ $# -lt 1 ]; then
    echo "Usage: `basename $0` sm1 [sm2 sm3...]"
    exit 1
fi

for sm in "$@"; do
    if [ -f "macs/$sm.txt" ]; then
        while read machine; do
            name=`echo $machine | cut -d':' -f1 | tr -d ' '`
            mac=`echo $machine | cut -d':' -f2- | tr -d ' '`
            echo -n "[$sm] $name : "
            etherwake $mac -i eth30
        done < macs/$sm.txt
    else
        echo "SM $sm has not been mapped yet."
    fi
done
