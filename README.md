# BeagleBone Black

## Supported capes
The `uEnv.txt` contained in the `/resources` folder was teste with:
* [4.3'' LCD Display Cape](https://community.element14.com/products/devtools/product-pages/w/documents/22398/4-3-lcd-display-cape-for-beaglebone-board-white-black-or-wireless)
* [Wireless Connectivity Cape](https://community.element14.com/products/devtools/product-pages/w/documents/22073/wireless-connectivity-cape-for-beaglebone-black)

Please, pay attention that:
* The USB port isn't able to supply enought current to guarantee that the board works properly with any of the capes above connected. Consider to use an external power supply that deliver at least 2.5 mA
* The Wireless Connectivity Cape and the touch screen enbedded on the LCD screen use the same GPIO to communicate with the UART. So they can't be used simoultaneusly

## Projects
* [Element14 - Roadtest](./element14-roadtest)
* [Home Router](./home-router)
