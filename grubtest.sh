make kernelmemfs
cp kernelmemfs grubcd/boot/
mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -V sel4test -o xv6.iso grubcd
qemu-system-i386 -cdrom xv6.iso -m 512
