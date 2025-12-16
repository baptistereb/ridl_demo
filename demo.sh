#!/bin/bash

GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

log() {
    echo -e "${GREEN}[+] ${NC}$1"
}

info() {
    echo -e "${CYAN}    $1${NC}"
}

log "Opening terminals..."

xterm -T "VICTIM" -bg black -fg white -fa 'Monospace' -fs 15 -geometry 67x50-0+0 -e \
    "cd scripts && make; bash" &

xterm -T "ATTACKER" -bg black -fg white -fa 'Monospace' -fs 15 -geometry 67x50+0+0 -e \
    "cd scripts; bash" &

log "Demo ready!"