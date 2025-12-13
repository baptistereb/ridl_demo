# RIDL Side-Channel Attack Demo (TLS-SEC, INSA Toulouse)

This repository hosts a demonstration of the **Rogue In-Flight Data Load (RIDL)** side-channel vulnerability, created for a **TLS-SEC (INSA Toulouse)** presentation.

The demo implements an attacker leaking a secret written by a victim using a speculative, unaligned load combined with an RSB misprediction and a Flush+Reload side-channel.

**Acknowledgment:**
This implementation is heavily inspired by the original research and the Proof-of-Concept found at **[github.com/vusec/ridl/blob/master/pocs/alignment_write.c](https://github.com/vusec/ridl/blob/master/pocs/alignment_write.c)**. Credit for the core technique goes to the original authors of the RIDL paper and PoC.