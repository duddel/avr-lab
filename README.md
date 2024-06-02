# AVR Lab

[![build](https://github.com/duddel/avr-lab/actions/workflows/build.yml/badge.svg)](https://github.com/duddel/avr-lab/actions/workflows/build.yml)

:alien: **Template and Examples in `C` for AVR Microcontrollers, optionally built via Docker.**

-   Using default `gcc-avr` and `avr-libc`, see [Dockerfile](Dockerfile) for details
-   Mainly written for `ATtiny85`, if not stated otherwise
-   Check out the examples in [src/](src/)
-   Utilize existing code for an own project or start with a basic example
-   Having Docker in place, the projects can be built with a single command

## Set up Docker

A Docker installation and basic Docker knowledge is required. Run these commands in the repository root.

First, build the Docker image (once).

```bash
docker build -t avrlab .
```

### Build a project

This builds a project in an auto-removing container, from the image created above. **Recommended in most cases.**

```bash
# Bash
docker run --rm -v $(pwd):/code avrlab /bin/bash -c "cd src/blink && make hex"

# Powershell
docker run --rm -v ${PWD}:/code avrlab /bin/bash -c "cd src/blink && make hex"
```

### Advanced (more Control over Container)

Start container with interactive shell.

```bash
# Option 1: Auto-removing container after usage
# Bash
docker run --rm -it -v $(pwd):/code avrlab

# Powershell
docker run --rm -it -v ${PWD}:/code avrlab

# Option 2: Named container
# Bash
docker run -it -v $(pwd):/code --name avrlab_01 avrlab

# Powershell
docker run -it -v ${PWD}:/code --name avrlab_01 avrlab

# For option 2, start container like this
docker start -i avrlab_01
```

Build a project.

```bash
cd src/blink
make hex
```

## avrdude Example Commands

-   Install `avrdude` on host (recommended)
-   Use `stk500v1` compatible ISP (e.g. using Arduino with ISP example sketch)

### Program

```bash
avrdude -p attiny85 -P com3 -c stk500v1 -b 19200 -U flash:w:main.hex
```

### Fuses

>   **Attention:** inappropriate fuse settings can brick the microcontroller, check **[1]**

```bash
# Set 1MHz clock
avrdude -p attiny85 -P com3 -c stk500v1 -b 19200 -U lfuse:w:0x62:m

# Set 8MHz clock
avrdude -p attiny85 -P com3 -c stk500v1 -b 19200 -U lfuse:w:0xE2:m
```

## References

**[1]** https://www.engbedded.com/fusecalc/

## License

The source code in this repository is licensed under the [MIT license](LICENSE.txt) (if not stated otherwise). For Licenses of thirdparty components, see below.
   
## Thirdparty

### Makefile_template

-   origin: `WinAVR-20100110`
-   license: see [Makefile_template](Makefile_template)
-   each example project in [src/](src/) contains a `Makefile`, which is an adjusted copy of [Makefile_template](Makefile_template)

### ws2812b_attiny13

-   version: **a98438c**
-   origin: https://github.com/dsprenkels/ws2812b_attiny13/tree/a98438c8b0572c430f73fb759fdab2607b238586
-   extracted from origin:
    -   `LICENSE`
    -   `ws2812b_attiny13.{c,h}`
-   modifications are marked with `AVR_LAB`
-   license: [src/ws2812b_attiny13_LICENSE](src/ws2812b_attiny13_LICENSE)
