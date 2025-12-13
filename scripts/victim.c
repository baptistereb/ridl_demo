/* victim.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <emmintrin.h> // Pour les instructions SSE2 (_mm_set1_epi8)

#define SECRET_VALUE 0x40

#define NC    "\033[0m"
#define GREEN "\033[0;32m"
#define CYAN  "\033[0;36m"
#define RED   "\033[0;31m"
void print_log(const char *msg) {printf(GREEN "[+] " NC "%s\n", msg);}
void print_info(const char *msg) {printf(CYAN "    %s" NC "\n", msg);}

int main() {
    char *buffer = aligned_alloc(64, 4096);
    char msg_buffer[256];
        
    print_log("Victim process started.");

    if (!buffer) {
        printf(RED "[FATAL] " NC "Memory allocation failed.\n");
        return 1;
    }

    snprintf(msg_buffer, sizeof(msg_buffer), "Buffer address: %p", buffer);
    print_info(msg_buffer);
    
    snprintf(msg_buffer, sizeof(msg_buffer), 
             "PID: %d. Writing secret 0x%x to memory...", getpid(), SECRET_VALUE);
    print_log(msg_buffer);
    
    printf("---------------------------------------------------\n");


    // (16 octets du secret 0x40)
    __m128i secret = _mm_set1_epi8(SECRET_VALUE);

    while (1) {
        // On écrit le secret dans le buffer en boucle
        // on utilise l'ASM volatile pour pas avoir les optimisations
        
        // Option 1: Écriture vectorielle (simule fork_vectorwrite_secret.inc)
        _mm_store_si128((__m128i *)buffer, secret);
        
        // Option 2: Force la vidange vers les buffers
        asm volatile("mfence" ::: "memory");
    }

    return 0;
}