#include "os.h"



void page_table_update(uint64_t pt, uint64_t vpn, uint64_t ppn) {
    uint64_t curr_pt_pa = pt;
    curr_pt_pa = curr_pt_pa << 0xC;
    uint64_t *curr_pt_va;
    uint64_t curr_pt_vpo;
    int lvl;
    for (lvl = 4; lvl > 0; lvl--) {
        /* get virt pointer to the current tp */
        curr_pt_va = phys_to_virt(curr_pt_pa);

        /* get the offset for in the current pt*/
        curr_pt_vpo = 0x1FF & (vpn >> (0x9 * lvl));

        /* check validity */
        if ((curr_pt_va[curr_pt_vpo] & 1) == 0) {
            if (ppn == NO_MAPPING) {
                return;
            }
            curr_pt_va[curr_pt_vpo] = (alloc_page_frame() << 0xC) | 0x1;
        }

        /* continue traversing */
        curr_pt_pa = 0xFFFFFFFFFFFFFFFE & curr_pt_va[curr_pt_vpo];
    }

    /* leaf reached */
    curr_pt_vpo = 0x1FF & vpn;
    curr_pt_va = phys_to_virt(curr_pt_pa);
    if (ppn == NO_MAPPING) {
        curr_pt_va[curr_pt_vpo] = 0;
        return;
    }
    curr_pt_va[curr_pt_vpo] = (ppn << 0xC) | 0x1;
}





uint64_t page_table_query(uint64_t pt, uint64_t vpn) {
    uint64_t curr_pt_pa = pt;
    curr_pt_pa = curr_pt_pa << 0xC;
    uint64_t *curr_pt_va;
    uint64_t curr_pt_vpo;
    int lvl;
    for (lvl = 4; lvl >= 0; lvl--) {
        /* get virt pointer to the current tp */
        curr_pt_va = phys_to_virt(curr_pt_pa);
        /* get the offset for in the current pt*/
        curr_pt_vpo = 0x1FF & (vpn >> (0x9 * lvl));
        /* check validity */
        if ((curr_pt_va[curr_pt_vpo] & 1) != 0) {
            /* continue traversing */
            curr_pt_pa = 0xFFFFFFFFFFFFFFFE & curr_pt_va[curr_pt_vpo];
        }
        else {
            return NO_MAPPING;
        }
    }
    /* leaf reached */
    return curr_pt_va[curr_pt_vpo] >> 0xC;
}

