# Network Repeater
## TL;DR
In this project I tried to configure the BeagleBone Black (*BBB*) and the network cape to emulate a network gateway. The requirement was to create a tether repeater, to convert a 4G USB stick connection to a WiFi connection.

## Tecnical requirements
* OS: [AM3358 Debian 10.3 2020-04-06 4GB SD IoT](https://debian.beagleboard.org/images/bone-debian-10.3-iot-armhf-2020-04-06-4gb.img.xz)
  For the complete list of the leastest available distribution, please refer to the official [bb website](https://beagleboard.org/latest-images)

* Network configurations: [/etc/network/interfaces](./interfaces)

## Configuration steps
1. Donwnload the [AM3358 Debian 10.3 2020-04-06 4GB SD IoT](https://debian.beagleboard.org/images/bone-debian-10.3-iot-armhf-2020-04-06-4gb.img.xz) debian-based os, and flash it on a at least 4GB SD card.
For the complete list of the least available distribution, please refer to the official [bb website](https://beagleboard.org/latest-images)

2. Plug the *Wireless Connectivity Cape* on the BBB and put the SD card inside its slot.

3. Start the BBB

4. Because of the proposed OS is slightly outdate, I suggest to update all software before continue the configuration, and expand the main partition to fit with the entire SD Card:
```
sudo apt-get update
sudo apt-get upgrade
sudo apt full-upgrade

sudo /opt/scripts/tools/grow_partition.sh
```

5. In order to make the `wlan0` interface available, update your `/boot/uEnv.txt` file with [this one](./boot/uEnv.txt) and reboot the system

6. To enable interfaces bridging, install the `bridge-utils` and `hostapd` packages
```
sudo apt-get install bridge-utils hostapd
```

7. Update your `/etc/network/interfaces` as described [here](./etc/network/interfaces), and your `/etc/hostapd/hostapd.conf` as described [here](./etc/hostapd/hostapd.conf).

> **NOTE:** the proposed solution was designed to enable a single hostapd profile. Furthermore, the `hostapd.conf` file must be updated accordingly with your needed.

8. Reboot the system to persist configurations

9.  If needed, update your `/etc/resolv.conf` file with additional DNS
```
nameserver 8.8.8.8 # Google primary DNS
nameserver 8.8.4.4 # Google secondary DNS
nameserver 1.1.1.1 # Cloudflare DNS
```

10. To complete the configuration, enable `hostapd` service, anche restart all involved services
```
sudo systemctl unmask hostapd
sudo systemctl start hostapd

sudo /etc/init.d/network restart
sudo /etc/init.d/hostapd restart
```

### Resources
* [openthread.io](https://openthread.io/guides/border-router/beaglebone-black)
* [guide.debianizzati.org](https://guide.debianizzati.org/index.php/Ethernet_Bridging)
