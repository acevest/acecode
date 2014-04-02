rm -f /boot/Beta.New
cp Beta /boot/Beta.New

rm -rf /boot/beta/
mkdir /boot/beta/
cp servers/mm/mm /boot/beta/
cp servers/init/init /boot/beta/

cp servers/mm/mm ./iso/boot/mod.mm
cp servers/init/init ./iso/boot/mod.init

mv  Beta ./iso/boot/Beta
rm -f ./iso/boot/grub/grub.cfg
cp ./scripts/grub.cfg ./iso/boot/grub/
grub2-mkrescue -o grub.iso iso

