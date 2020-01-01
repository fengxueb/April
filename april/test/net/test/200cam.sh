#!/bin/bash
echo hello
#ip="192.168.1.2"
#mac="00:1f:55:65:32:01"


for i in {2..3}
do
ip=`printf "192.168.1.%d " $i`
mac=`printf "00:1f:55:2f:ac:%02x" $i`
 
 ./udpserver $ip  $mac &

#./udpserver 192.168.1.$(expr $i + 1) 00:1f:55:2f:ac:$(expr $i + 1) &

done

