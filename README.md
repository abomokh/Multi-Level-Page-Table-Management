# Multi-Level Page Table Management

This repository contains an implementation of Multi-Level Page Table Management in C. It demonstrates fundamental concepts of virtual memory and page tables, such as updating page table entries and querying virtual-to-physical memory mappings.

## Files
- **pt.c**: Contains the core functions for page table updates and queries.
  - `page_table_update(uint64_t pt, uint64_t vpn, uint64_t ppn)`: Updates the page table to map a virtual page number (VPN) to a physical page number (PPN).
  - `page_table_query(uint64_t pt, uint64_t vpn)`: Queries the mapping of a given VPN and returns the corresponding PPN.

- **os.h**: Header file defining constants and function prototypes, including:
  - `NO_MAPPING`: A constant representing the absence of a mapping.
  - Memory management helpers: `alloc_page_frame` and `phys_to_virt`.

- **os.c**: Contains helper functions for memory allocation and translation between physical and virtual addresses, as well as a test suite to verify the functionality of the page table management.

## Usage
1. Clone the repository:
   ```bash
   git clone https://github.com/<your-username>/multi-level-page-table.git
   cd multi-level-page-table

2. Compile the code:
  ```bash
  gcc -o page_table os.c pt.c

3. Run the program:
  ```bash
  ./page_table
