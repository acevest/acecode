IMGFILE=../HD.IMG
#8*16*63=8046
#dd if=/dev/zero of=$IMGFILE bs=512 count=8064
dd if=/dev/zero of=$IMGFILE bs=512 count=163296
sudo losetup /dev/loop0 $IMGFILE
echo '+-----------------------------------------+'
echo '| INPUT: o n p 1 <return> <return> a 1 p w|'
echo '+-----------------------------------------+'
#sudo fdisk -u -C8 -H16 -S63 /dev/loop0
cat <<EOF | fdisk -u -C162 -H16 -S63 /dev/loop0 > /dev/null
o
n
p
1


a
1
p
w
EOF

echo 'Making File System'
sudo mkfs.ext2 /dev/loop0
sudo sync
sudo losetup -d /dev/loop0

