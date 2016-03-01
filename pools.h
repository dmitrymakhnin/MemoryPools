#ifndef POOLS_H
#define POOLS_H

#include <stdlib.h>
#include <stdint.h>
#include <vector>

namespace pools 
{
    #define ref_max 100

    /* really useful info for an allocator/deallocator. */
    typedef struct {
        uint8_t *addr;         /* starting address. */
        size_t size;        /* allocated block size. */
        size_t pool_index;  /* relative to pool array position. */     
    } mempart_t;

    /* memory management table. */    
    extern std::vector<mempart_t *> full_blocks;
    extern std::vector<mempart_t *> free_blocks;
 
    /* somebody has to make the pool. */
    extern const size_t default_size;  /* bytes */
    extern uint8_t *ppool;

    /* raw memory allocator. */
    void *malloc(size_t size);

    /* deallocator. */
    void free(void *ptr);

    /* helper */
    void report_status(void);

    /* constructor. */
    void init(void);
};

#endif /* POOLS_H */