# Cassandra Work Distribution Simulator

This a small program which uses a very nice [Murmur 3](https://github.com/PeterScott/murmur3) implementation to simulate how data gets distributed around a Cassandra cluster's "ring".

Simple usage:

```sh
$ make
$ ./cass-wd 5 my_key
node points:
srv0 => -1758912239
srv1 => -1130950360
srv2 => -639705568
srv3 => 1312006379
srv4 => 1332396479
key "my_key" hashes to 324067178 and is predicted to land on node 3/4
```
There is also a packaged script, `count.sh`, which runs a larger simulation modeled after a metric from a [Snap](https://github.com/intelsdi-x/snap) collector plugin: https://github.com/intelsdi-x/snap-plugin-collector-cpu.  The script runs a simulation where this metric is being collected across _n_ machines (5 by default), each with 72 cores.

```sh
$ ./count.sh
node 0 has 216 keys
node 1 has 106 keys
node 2 has 73 keys
node 3 has 323 keys
node 4 has 2 keys
```


Here's a graphical representation of those results:

<img width="798" alt="screen shot 2016-08-19 at 9 29 39 pm" src="https://cloud.githubusercontent.com/assets/1194436/17829093/64809828-6657-11e6-9d06-2f31337ca448.png">

If you so desire, a node count can also be passed in to simulate clusters of varying sizes:
```sh
$ ./count.sh 9
node 0 has 146 keys
node 1 has 0 keys
node 2 has 70 keys
node 3 has 38 keys
node 4 has 68 keys
node 5 has 73 keys
node 6 has 125 keys
node 7 has 198 keys
node 8 has 2 keys
```
