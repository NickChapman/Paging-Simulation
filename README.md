To run this program simply do

```
cmake .
make
./nlc35.exe <number of frames> <algorithm to use> [verbose]

Available algorithms:
	FIFO: First In, First Out
	GC: Global Clock
	LFU: Least Frequently Used
	LRU: Least Recently Used
	RAND: Random
	OWN: LRU Antithrashing
```