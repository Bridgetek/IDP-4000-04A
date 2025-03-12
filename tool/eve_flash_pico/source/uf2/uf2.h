/**

Microsoft UF2

The MIT License (MIT)

Copyright (c) Microsoft Corporation

All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#ifndef UF2FORMAT_H
#define UF2FORMAT_H 1

#include <stdint.h>
#include <stdbool.h>

#include "board_api.h"

//--------------------------------------------------------------------+
// UF2 Configuration
//--------------------------------------------------------------------+

// Version is passed by makefile
// #define UF2_VERSION         "0.0.0"

#define CFG_UF2_FLASH_SIZE          (256*1024*1024)  // TODO absolute max flash size
#define CFG_UF2_NUM_BLOCKS          (0x300000)       // 1.5 GB
#define CFG_UF2_SECTORS_PER_CLUSTER (64)

//--------------------------------------------------------------------+
//
//--------------------------------------------------------------------+

// All entries are little endian.
#define UF2_MAGIC_START0    0x0A324655UL // "UF2\n"
#define UF2_MAGIC_START1    0x9E5D5157UL // Randomly selected
#define UF2_MAGIC_END       0x0AB16F30UL // Ditto

// If set, the block is "comment" and should not be flashed to the device
#define UF2_FLAG_NOFLASH    0x00000001
#define UF2_FLAG_FAMILYID   0x00002000

#define MAX_BLOCKS (CFG_UF2_FLASH_SIZE / 256 + 100)
typedef struct {
    uint32_t numBlocks;
    uint32_t numWritten;

    bool aborted;             // aborting update and reset

// writtenMask = flash size / 256 / 8 = block no  / 8 
//             => each block is represented by 1 bit
//             If flash size = 256MB, block size = 1024*1024, need 1Mb/8=128kb
#if defined(REDUCE_WRITTENMASK) && REDUCE_WRITTENMASK == 1
#define NUM_WRITTENMASK 1000
    uint8_t writtenMask[NUM_WRITTENMASK];
#else
    uint8_t writtenMask[MAX_BLOCKS / 8 + 1];
#endif

} WriteState;

typedef struct {
    // 32 byte header
    uint32_t magicStart0;
    uint32_t magicStart1;
    uint32_t flags;
    uint32_t targetAddr;
    uint32_t payloadSize;
    uint32_t blockNo;
    uint32_t numBlocks;
    uint32_t familyID;

    // raw data;
    uint8_t data[476];

    // store magic also at the end to limit damage from partial block reads
    uint32_t magicEnd;
} UF2_Block;


void uf2_init(void);
void uf2_read_block(uint32_t block_no, uint8_t *data);
int  uf2_write_block(uint32_t block_no, uint8_t *data, WriteState *state);

#endif
