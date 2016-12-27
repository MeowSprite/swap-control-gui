#!/bin/bash
ECHO(){
    echo $1=$(eval echo \$$1)
}
# get cpu count from cpuinfo
cpu_count=$(nproc)
# get total ram size for meminfo
ram_size=$(awk '/MemTotal:/ { print $2 }' /proc/meminfo)
. $1

ECHO cpu_count
ECHO ram_size

ECHO zswap_enabled
ECHO zswap_compressor
ECHO zswap_max_pool_percent
ECHO zswap_zpool

ECHO zram_enabled
ECHO zram_size
ECHO zram_streams
ECHO zram_alg
ECHO zram_prio

ECHO swapfu_enabled
ECHO swapfu_size
ECHO swapfu_path
ECHO swapfu_prio

ECHO swapfc_enabled
ECHO swapfc_chunk_size
ECHO swapfc_max_count
ECHO swapfc_free_swap_perc
ECHO swapfc_path

ECHO swapd_auto_swapon