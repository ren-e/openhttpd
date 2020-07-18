# OpenBSD httpd
The OpenBSD httpd webserver with minor adjustments to work on Linux.

### Requirements
  - Debian Linux
  - libbsd >= 0.9.1
  - libressl >= 3.1.3
  - libevent >= 2.1.8
  - freebsd-buildutils >= 10.3

### Install dependencies
```
apt-get install libbsd-dev libevent-dev libressl freebsd-buildutils
```
### Compile
```
fmake
```

### Installation
You'll need to create all depending directories.
