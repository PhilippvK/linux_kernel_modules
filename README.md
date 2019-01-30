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

There may be more details in the README of the directory itself.

## Inspirations

* [https://github.com/tleonhardt/linux_lkm/blob/master/README.md](https://github.com/tleonhardt/linux_lkm/blob/master/README.md) - LKM READE and examples
* TODO

## Authors

* **Philipp van Kempen** - *only Developer* - [phi.philonata.de](https://phi.philonata.de)

## License

This project is licensed under the GNU License - see the [LICENSE.md](LICENSE.md) file for details

