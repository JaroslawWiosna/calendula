
```console
$ ./calendula 
    March 2021
Mo Tu We Th Fr Sa Su 
 1  2  3  4  5  6  7 
 8  9 10 11 12 13 14 
15 16 17 18 19 20 21 
22 23 24 25 26 27 28 
29 30 31 
$ ./calendula --version
calendula 0.2.0
$ ./calendula --help
Usage:
 ./calendula [options]

Options:
 -s, --sunday     Sunday as first day of week
 -m, --monday     Monday as first day of week
     --tuesday    Tuesday as first day of week
     --wednesday  Wednesday as first day of week
     --thursday   Thursday as first day of week
     --friday     Friday as first day of week
     --saturday   Saturday as first day of week
 -V, --version    display version information and exit
 -h, --help       display this help text and exit

```

The source code of `cal` is here https://github.com/karelzak/util-linux/blob/31862cde0a0551b42e6b84015da7719a784007d9/misc-utils/cal.c 
