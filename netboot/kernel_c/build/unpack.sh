if [ ! -f cluster.iso ]; then
    wget http://mlc.underflow.fr/cluster.iso
fi
if [ -d extract ]; then
    sudo rm -rf extract
fi

echo "Creating extract dir"
mkdir -p extract/tmp/mnt
echo "Mounting iso image"
sudo mount cluster.iso extract/tmp/mnt -o loop,ro
echo "Extracting iso"
sudo cp -a extract/tmp/mnt/boot extract/tmp
sudo mv extract/tmp/boot/core.gz extract/tmp
echo "Unmounting iso image"
sudo umount extract/tmp/mnt
sudo rmdir extract/tmp/mnt
echo "Extracting initrd"
mkdir extract/initrd
cd extract/initrd
zcat ../tmp/core.gz | sudo cpio -i -H newc -d
cd ../..
echo "Extracting bootloader"
sudo cp extract/tmp/boot extract/boot -R
sudo rm -rf extract/tmp
echo "extract folder is ready !"
