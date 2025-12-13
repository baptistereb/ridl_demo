SCRIPT = demo.sh

all: start

start:
	@chmod +x $(SCRIPT)
	@echo "[*] Launching the demo..."
	./$(SCRIPT)