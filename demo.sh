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

SSH_OPTS="-o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no"

xterm -T "VICTIM" -bg black -fg white -fa 'Monospace' -fs 15 -geometry 67x50-0+0 -e \
    "echo 'Connecting to VICTIM...'; ssh $SSH_OPTS victim@server; bash" &

xterm -T "ATTACKER" -bg black -fg white -fa 'Monospace' -fs 15 -geometry 67x50+0+0 -e \
    "echo 'Connecting to EVE...'; ssh $SSH_OPTS attack@server; bash" &

log "Demo ready!"