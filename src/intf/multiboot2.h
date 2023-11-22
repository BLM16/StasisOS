#pragma once

#include <stdint.h>
#include "util/attributes.h"

#define MB2_MAGIC 0x36D76289

#define MB2_TYPE_END          0
#define MB2_TYPE_CMDLINE      1
#define MB2_TYPE_BOOTLOADER   2
#define MB2_TYPE_MODULES      3
#define MB2_TYPE_MEMINFO      4
#define MB2_TYPE_BIOSDEV      5
#define MB2_TYPE_MEMMAP       6
#define MB2_TYPE_VBEINFO      7
#define MB2_TYPE_FBUFFINFO    8
#define MB2_TYPE_ELFSYMBOLS   9
#define MB2_TYPE_APMTABLE     10
#define MB2_TYPE_EFISYSTAB32  11
#define MB2_TYPE_EFISYSTAB64  12
#define MB2_TYPE_SMBIOSTAB    13
#define MB2_TYPE_ACPIOLD      14
#define MB2_TYPE_ACPINEW      15
#define MB2_TYPE_NETWORK      16
#define MB2_TYPE_EFIMEMMAP    17
#define MB2_TYPE_EFIBOOTNT    18
#define MB2_TYPE_EFIIMGHND32  19
#define MB2_TYPE_EFIIMGHND64  20
#define MB2_TYPE_IMGLDBPA     21

#define MB2_MEM_AVAILABLE   1
#define MB2_MEM_RESERVED    2
#define MB2_MEM_USABLE_ACPI 3
#define MB2_MEM_PRESERVE    4
#define MB2_MEM_DEFECTIVE   5

#define MB2_FBUFF_TYPE_INDEXED  0
#define MB2_FBUFF_TYPE_RGB      1
#define MB2_FBUFF_TYPE_EGA_TEXT 2

typedef struct __packed MB2_tag {
    uint32_t type;
    uint32_t size;
} MB2_tag;

typedef struct __packed MB2_information_structure {
    uint32_t size;
    uint32_t reserved;
} MB2_information_structure;

typedef struct __packed MB2_tag_cmdline {
    uint32_t type;
    uint32_t size;
    uint8_t* string;
} MB2_tag_cmdline;

typedef struct __packed MB2_tag_bootloader {
    uint32_t type;
    uint32_t size;
    uint8_t* string;
} MB2_tag_bootloader;

typedef struct __packed MB2_tag_modules {
    uint32_t type;
    uint32_t size;
    uint32_t mod_start;
    uint32_t mod_end;
    uint8_t* string;
} MB2_tag_modules;

typedef struct __packed MB2_tag_meminfo {
    uint32_t type;
    uint32_t size;
    uint32_t mem_lower;
    uint32_t mem_upper;
} MB2_tag_meminfo;

typedef struct __packed MB2_tag_biosdev {
    uint32_t type;
    uint32_t size;
    uint32_t biosdev;
    uint32_t partition;
    uint32_t sub_partition;
} MB2_tag_biosdev;

typedef struct __packed MB2_memmap_entry {
    uint64_t base_addr;
    uint64_t length;
    uint32_t type;
    uint32_t reserved;
} MB2_memmap_entry;

typedef struct __packed MB2_tag_memmap {
    uint32_t type;
    uint32_t size;
    uint32_t entry_size;
    uint32_t entry_version;
    MB2_memmap_entry* entries;
} MB2_tag_memmap;

typedef struct __packed MB2_tag_vbeinfo {
    uint32_t type;
    uint32_t size;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
    uint8_t  vbe_control_info[512];
    uint8_t  vbe_mode_info[256];
} MB2_tag_vbeinfo;

typedef struct __packed MB2_color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} MB2_color;

typedef struct __packed MB2_tag_fbuffinfo {
    uint32_t type;
    uint32_t size;
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t  framebuffer_bpp;
    uint8_t  framebuffer_type;
    uint8_t  reserved;
    
    union color_info
    {
        struct {
            uint16_t framebuffer_palette_num_colors;
            MB2_color* framebuffer_palette;
        };
        struct {
            uint8_t framebuffer_red_field_position;
            uint8_t framebuffer_red_mask_size;
            uint8_t framebuffer_green_field_position;
            uint8_t framebuffer_green_mask_size;
            uint8_t framebuffer_blue_field_position;
            uint8_t framebuffer_blue_mask_size;
        };
    };
} MB2_tag_fbuffinfo;

typedef struct __packed MB2_tag_efisystab32 {
    uint32_t type;
    uint32_t size;
    uint32_t pointer;
} MB2_tag_efisystab32;

typedef struct __packed MB2_tag_efisystab64 {
    uint32_t type;
    uint32_t size;
    uint64_t pointer;
} MB2_tag_efisystab64;

typedef struct __packed MB2_tag_smbiostab {
    uint32_t type;
    uint32_t size;
    uint8_t major;
    uint8_t minor;
    uint8_t reserved[6];
    uint8_t* smbios_tables;
} MB2_tag_smbiostab;

typedef struct __packed MB2_tag_acpiold {
    uint32_t type;
    uint32_t size;
    uint8_t* rsdp;
} MB2_tag_acpiold;

typedef struct __packed MB2_tag_acpinew {
    uint32_t type;
    uint32_t size;
    uint8_t* rsdp;
} MB2_tag_acpinew;

typedef struct __packed MB2_tag_network {
    uint32_t type;
    uint32_t size;
    uint8_t* dhcpack;
} MB2_tag_network;

typedef struct __packed MB2_tag_efimemmap {
    uint32_t type;
    uint32_t size;
    uint32_t descriptor_size;
    uint32_t descriptor_version;
    uint8_t* efi_memmap;
} MB2_tag_efimemmap;

typedef struct __packed MB2_tag_efibootnt {
    uint32_t type;
    uint32_t size;
} MB2_tag_efibootnt;

typedef struct __packed MB2_efiimghnd32 {
    uint32_t type;
    uint32_t size;
    uint32_t pointer;
} MB2_efiimghnd32;

typedef struct __packed MB2_efiimghnd64 {
    uint32_t type;
    uint32_t size;
    uint64_t pointer;
} MB2_efiimghnd64;

typedef struct __packed MB2_tag_imgldbpa {
    uint32_t type;
    uint32_t size;
    int32_t load_base_addr;
} MB2_tag_imgldbpa;
