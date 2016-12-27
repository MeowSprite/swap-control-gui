#!/bin/bash

INFO(){ echo -n "INFO: "; echo "$@" ;}
WARN(){ echo -n "WARN: "; echo "$@" ;}
ERRO(){ echo -n "ERRO: "; echo -n "$@" ; echo " Abort!"; exit 1;}

help() {
    echo "do not run this script mannually"
    echo "$0 zswap [enabled] [max_pool_percent] [zpool] [compressor]"
    exit 2
}

check_root_rights(){ [ $(id -u) = 0 ] || ERRO "Script must be run as root!"; }

case $1 in
    zswap)
        INFO "set zswap"
        check_root_rights
        ZSWAP_P=/sys/module/zswap/parameters  
        echo $2 > $ZSWAP_P/enabled
        echo $4 > $ZSWAP_P/max_pool_percent
        echo $5 > $ZSWAP_P/zpool
        echo $3 > $ZSWAP_P/compressor
        INFO "Zswap: set new parameters complete"
    ;;

    *) help;;
esac
exit 0