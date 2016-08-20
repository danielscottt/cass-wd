#! /bin/bash

NODE_COUNT=$1
NODE_COUNT="${NODE_COUNT:-5}"

for i in `seq 0 $(($NODE_COUNT-1))`; do echo "node $i has $(for j in `seq 0 71`; do for k in `seq 0 9`; do ./cass-wd $NODE_COUNT "/intel/procfs/cpu/$j/steal_percentage,1,srv_$k"; done; done | grep "node $i" | wc -l) keys"; done
