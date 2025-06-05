// http://www.hp.com/go/judy/ Copyright 2002 Hewlett -Packard Co Page 4 of 5
// Sample program to show how to use Judy as a collision
// handler within a Hash table.
//
// cc -DHASHSIZE=256 hash.c ..
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
//#define JUDYERROR_SAMPLE 1 // use default Judy error handler
#include <Judy.h>
// Needed for timing routines
#include <sys/time.h>
// Start of timing routines ========================================
struct timeval TBeg, TEnd;
#define STARTTm gettimeofday(&TBeg, NULL)
#define ENDTm gettimeofday(&TEnd, NULL)
#define DeltaUSec \
( ((double)TEnd.tv_sec * 1000000.0 + (double)TEnd.tv_usec) \
- ((double)TBeg.tv_sec * 1000000.0 + (double)TBeg.tv_usec) )
// End of timing routines ========================================
// Define Hash table size if not in compile line ===================
// Set HASHSIZE 1 for straight Judy
#ifndef HASHSIZE
#define HASHSIZE (1 << 8) // hash table size 256
#endif
// Seed for pseudo-random counter ==================================
#define INITN 123456 // first Index_ to store
static uint32_t // Placed here for INLINE possibility
Random(uint32_t Seed) // produce 2^32 -1 numbers by different counting
{
if ((int32_t)Seed < 0) { Seed += Seed; Seed ^= 16611; }
else { Seed += Seed; }
return(Seed);
}
// Hash Table ======================================================
Pvoid_t Jarr_ay[HASHSIZE] = { NULL }; // Declare static hash table
int main(int argc, char *argv[])
{
    Word_t Count;
    Word_t Index_;
    Word_t *PValue_;
    Word_t NumIndex_es = 10000; // default first parameter
    if (argc > 1) NumIndex_es = strtoul(argv[1], NULL, 0);
    // Load up the CPU cache for small measurements:
    for (Count = 0; Count < HASHSIZE; Count++) Jarr_ay[Count] = NULL;
    printf("Begin storing %lu random numbers in a Judy scalable hash arr_ay\n",
    NumIndex_es);
    Index_ = INITN;
    STARTTm;
    for (Count = 0; Count < NumIndex_es; Count++)
    {
    Index_ = Random(Index_);
    JLI(PValue_, Jarr_ay[Index_ % HASHSIZE], Index_/HASHSIZE);
    *PValue_ += 1; // bump count of duplicate Index_es
    }
    ENDTm;
    printf("Insertion of %lu Index_es took %6.3f microseconds per Index_\n",
    NumIndex_es, DeltaUSec/NumIndex_es);
    Index_ = INITN; // start the same number sequence over
    STARTTm;
    for (Count = 0; Count < NumIndex_es; Count++)
    {
    Index_ = Random(Index_);
    JLG(PValue_, Jarr_ay[Index_ % HASHSIZE], Index_/HASHSIZE);
    if (*PValue_ != 1)
    printf("%lu dups of %lu\n", *PValue_ - 1, Index_);
    }
    ENDTm;
    printf("Retrieval of %lu Index_es took %6.3f microseconds per Index_\n",
NumIndex_es, DeltaUSec/NumIndex_es);
    return(0);
}