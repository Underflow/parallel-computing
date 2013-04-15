if [ ! -d extract ]; then
    echo "You should first unpack the iso : make unpack"
    exit 0
fi
sudo rm -rf extract/initrd/cluster/*
echo "Replacing cluster dir in the initrd"
sudo cp cluster/* extract/initrd/cluster -R
cd extract/initrd
find | sudo cpio -o -H newc | gzip -2 > ../core.gz
cd ..
#advdef -z4 core.gz
sudo mv core.gz boot
mkdir newiso
sudo mv boot newiso
echo "Making cluster.iso"
sudo mkisofs -l -J -R -V TC-cursom -no-emul-boot -boot-load-size 4 \
    -input-charset UTF-8 \
    -boot-info-table -b boot/isolinux/isolinux.bin \
    -c boot/isolinux/boot.cat -o cluster.iso newiso
cd ..
cp extract/cluster.iso .
sudo rm -rf extract
echo "cluster.iso has been packed"
sudo cp cluster.iso /mnt/pxeiso
echo "cluster.iso has been set in /mnt/pxeiso"
