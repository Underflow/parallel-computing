My Little Cluster
=================

TODO: Description of the project

Set up a dhcp and tftp server using dnsmasq
-------------------------------------------

dnsmasq is perfect for what we want, here is a sample config file, assuming you
have a `udionly.kpxe` pxe image in `/mnt/pxeiso` (but it is easily adaptable)

    port=0
    interface=eth0
    bind-interfaces
    dhcp-range=10.244.0.0,10.244.255.255
    dhcp-boot=/undionly.kpxe
    enable-tftp
    tftp-root=/mnt/pxeiso/
    next-server=localhost

(This dhcp-range works for the VJ PIE)
Then start dnsmasq deamon.


Build an ipxe image with embeded script
---------------------------------------
(If not already done, `git submodule init && git submodule update` or clone the
repository with `git clone --recursive`)

    cd ipxe/src
    make bin/undionly.kkpxe EMBED=path/to/your/script.ipxe

Your ipxe image is `bin/undionly.kpxe`, you can now copy it to the folder you
choose for the tftp server.

In order not to rebuild another script, you can build only the script
common.ipxe. This script is configured to retrieves another script at the
adress http://{next-server}:8042/static/current.ipxe.
You just have to launch the server in www/ and link the script you want to
start with in static/current.ipxe :
    
    cd www/static
    ln -s ../../ipxe_scripts/myscript.ipxe current.ipxe
    cd ..
    ./http_server.py
