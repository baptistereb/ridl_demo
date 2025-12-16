all: init clean build cpu

init:
	echo 16 | sudo tee /proc/sys/vm/nr_hugepages

clean:
	- rm victim attack

build:
	gcc -O2 victim.c -o victim
	gcc -O2 attack.c -o attack

cpu:
	lscpu -e
	@echo "Utilisez des CPU sur les même NODES et CORES ci dessus (modifiez le Makefile)"

run-victim:
	taskset -c 4 ./victim

run-attack:
	taskset -c 16 ./attack

vuln:
	cat /sys/devices/system/cpu/vulnerabilities/mds