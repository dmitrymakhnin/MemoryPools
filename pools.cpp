#include <stdio.h>
#include <assert.h>
#include "pools.h"

namespace pools
{
    #define DEFAULT_SIZE 0xffff
    /**
     * every program is entitled to
     * 0xffff stack memory to play with.
     */
    uint8_t pool[DEFAULT_SIZE];
    uint8_t *ppool = (uint8_t *)&pool[0];
    std::vector<mempart_t *> full_blocks;
    std::vector<mempart_t *> free_blocks; 
}

void pools::init(void)
{
    /* create a "friendly blob" of free space. */
    auto mp = new mempart_t;
    mp->addr = (uint8_t *)ppool;
    mp->size = DEFAULT_SIZE * sizeof(uint8_t);
    mp->pool_index = 0; 
    free_blocks.push_back(mp);

}

/**
 * searches the pool for a continuous memory block.
 *    it must consider all existing references.
 *    
 * I expect it to be expensive to do so.
 *
 * page 314 of operating systems briefly goes over
 *     best fit and first fit.
 * 
 * returns a pointer to the memory block.
 */
void *pools::malloc(size_t size)
{
    /* search for a free block willing to share. */
    for (auto it = free_blocks.begin(); it != free_blocks.end(); ++it) {
        mempart_t *tmp = (*it);
        if (tmp->size > size) {
            free_blocks.erase(it);
            full_blocks.push_back(tmp);
            return tmp->addr;
        }
    }

    return NULL;
}

/**
 * removes the <address, size> pair from manager,
 *     giving it more room to allocate from.
 *
 * the pointer points to the actual address.
 * the search should be longer than O(N).
 */
void pools::free(void *ptr)
{
    for (auto it = full_blocks.begin(); it != full_blocks.end(); ++it) {
        mempart_t *tmp = (*it);

        if (tmp->addr == ptr) {
            full_blocks.erase(it);
            free_blocks.push_back(tmp);  
            return;          
        }
    }
}

void pools::report_status(void)
{
    printf("pool size: %d.\n", DEFAULT_SIZE);    
    printf("reference table size: %d.\n", ref_max);
    printf("free blocks: %d.\n", pools::free_blocks.size());
    printf("full blocks: %d.\n", pools::full_blocks.size());
}