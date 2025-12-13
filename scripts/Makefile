all: clean build victim

clean: 
	- rm victim attack

build:
	gcc -O2 victim.c -o victim
	gcc -O2 attack.c -o attack

run victim:
	taskset -c 4 ./victim

run attack:
	taskset -c 16 ./attack

cpu:
	lscpu -e

vuln:
	cat /sys/devices/system/cpu/vulnerabilities/mds