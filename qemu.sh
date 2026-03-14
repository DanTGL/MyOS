#!/bin/sh
set -e
. ./iso.sh

HOSTARCH=$(./target-triplet-to-arch.sh $HOST)

: ${QEMU_FLAGS:=""}

if [[ -e "CODE_$HOSTARCH.fd" && -e "VARS_$HOSTARCH.fd" ]]; then
	QEMU_FLAGS+=" -drive if=pflash,format=raw,unit=0,file=CODE_$HOSTARCH.fd,readonly=on"
	QEMU_FLAGS+=" -drive if=pflash,format=raw,unit=1,file=VARS_$HOSTARCH.fd"
fi

qemu-system-$HOSTARCH -cdrom myos.iso -m 2G $QEMU_FLAGS
