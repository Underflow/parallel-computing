if [ ! -d extract ]; then
    echo "You should first unpack the iso : make unpack"
    exit 0
fi
rm -rf extract/initrd/cluster/*
echo "Replacing cluster dir in the initrd"
cp cluster/* extract/initrd/cluster -R
cd extract/initrd
find | cpio -o -H newc | gzip -2 > ../core.gz
cd ..
#advdef -z4 core.gz
mv core.gz boot
mkdir newiso
mv boot newiso
echo "Making cluster.iso"
genisoimage -l -J -R -V TC-cursom -no-emul-boot -boot-load-size 4 \
    -input-charset UTF-8 \
    -boot-info-table -b boot/isolinux/isolinux.bin \
    -c boot/isolinux/boot.cat -o cluster.iso newiso
cd ..
cp extract/cluster.iso .
rm -rf extract
echo "cluster.iso has been packed"
cp cluster.iso /mnt/pxeiso
echo "cluster.iso has been set in /mnt/pxeiso"
