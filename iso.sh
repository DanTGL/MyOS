#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/myos.kernel isodir/boot/myos.kernel
#cat > isodir/boot/grub/grub.cfg << EOF
#menuentry "myos" {
#	multiboot /boot/myos.kernel
#}
#EOF
#grub-mkrescue -o myos.iso isodir

if [ ! -f limine/limine ]; then
	git clone https://github.com/limine-bootloader/limine.git --branch=v10.x-binary --depth=1
  	make -C limine
fi

mkdir -p isodir/boot
#cp -v kernel/bin/kernel isodir/boot/
mkdir -p isodir/boot/limine
cp -v limine.conf limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin isodir/boot/limine/
mkdir -p isodir/EFI/BOOT
cp -v limine/BOOTX64.EFI isodir/EFI/BOOT/
cp -v limine/BOOTIA32.EFI isodir/EFI/BOOT/

# Create the bootable ISO.
xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
        -apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        isodir -o myos.iso