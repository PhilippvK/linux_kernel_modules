# Linux Kernel Modules by Philipp v. K.

This is a collection of simple Linux Kernel Modules I've written while learning about kernel programming for my bachelor thesis.

## Getting Started

If you are interested in this topic, I recommend you to read this first:
[https://en.wikipedia.org/wiki/Loadable_kernel_module](https://en.wikipedia.org/wiki/Loadable_kernel_module)

### Setup

I am using Raspberry Pi's as test systems but a simple Linux VM should work, too. There are modules which will work on Raspbian only!

First, you have to get the development tools for your kernel
```
sudo apt install linux-headers-$(uname -r)
```

### Usage

Every module should have a Makefile with at least the following targets 
```
make		# compile everything and create the .ko file
make clean	# clean everything except the source files
make load	# run insmod for your module
make unload	# run rmmod for the module
make test	# test the functionality by loading/unloading and displaying the logs
```

## List of Modules

* **lkm_example** (simple hello world module)
* **lkm_device** (character device module)
* **lkm_gpio** (using the gpio.h lib with the Raspberry Pi)
* **lkm_printstats** (calculate the CPU load for a single core)
* **lkm_loadled** (indicate high CPU loads with a LED)
* **lkm_helloparam** (parameterized hello world code)
* **lkm_chardevioctl** (test ioctl devices)
* **lkm_raspberry** (testing raspberry pi fireware calls)

There may be more details in the README of the directory itself.

### Planned Features (TODOs)

* load calculation for multi core processors (support RPi 3B+)
* Add intermediate CPU clock freqs for Raspberry if possible
* Try to implement cpufreq_interactive governor on Raspberry Pi's
* Read CPU and GPU temperature via ioctl
* Fan control depending on load and temperature

## Inspirations

* [https://github.com/tleonhardt/linux_lkm/blob/master/README.md](https://github.com/tleonhardt/linux_lkm/blob/master/README.md) - LKM READE and examples
* [https://www.apriorit.com/dev-blog](https://www.apriorit.com/dev-blog) - Tutorials for Device Drivers
* [https://blog.fazibear.me/the-beginners-guide-to-linux-kernel-module-raspberry-pi-and-led-matrix-790e8236e8e9](https://blog.fazibear.me/the-beginners-guide-to-linux-kernel-module-raspberry-pi-and-led-matrix-790e8236e8e9) - GPIO.h explained
* [TODO](TODO) - TODO 

## Authors

* **Philipp van Kempen** - *only Developer* - [phi.philonata.de](https://phi.philonata.de)

## License

This project is licensed under the GNU License - see the [LICENSE.md](LICENSE.md) file for details

