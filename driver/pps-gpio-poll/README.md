# pps-gpio-poll

pps-gpio-poll is a Linux kernel module which provides a `/dev/pps*` device
using a GPIO pin as the PPS source. With an NTP daemon like
[chrony](https://chrony.tuxfamily.org) or [ntpd](https://www.ntp.org) it can be
used to accurately synchronize the system clock with a reference time source.

Unlike the pps-gpio module (which is included in the Linux tree) it doesn't
use interrupts. It uses a high-resolution timer and waits for the GPIO value to
change in a busy loop instead. This means the PPS samples are more accurate and
have less jitter, but more CPU time is consumed. Another difference is that the
number of the GPIO pin is a parameter of the kernel module instead of relying
on Device Tree.

This is a continuation of the
https://code.google.com/archive/p/openwrt-stratum1/[openwrt-stratum1] project
by Gabs Ricalde.

Fork from [mlichvar/pps-gpio-poll](https://github.com/mlichvar/pps-gpio-poll).