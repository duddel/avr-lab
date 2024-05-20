# AVR Lab

:alien: **Template and Examples in `C` for AVR Microcontrollers, optionally built via Docker.**

-   Using default `gcc-avr` and `avr-libc`, see [Dockerfile](Dockerfile) for details
-   Check out the examples in [src/](src/)
-   Utilize existing code for an own project or start with a basic example
-   Having Docker in place, the projects can be built with a single command

## Set up Docker

A Docker installation and basic Docker knowledge is required.

1.  Build the Docker image.

```bash
docker build -t avrlab .
```

2.  Start container with interactive shell.

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

3.  Build a project.

```bash
cd src/blink
make hex
```

## avrdude Example Commands

-   Install `avrdude` on host
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

-   The source code in this repository is licensed under the [MIT license](LICENSE.txt) (if not stated otherwise)
-   [Makefile_template](Makefile_template) taken from `WinAVR-20100110`. See License in [Makefile_template](Makefile_template)
    -   Each example project in [src/](src/) contains a `Makefile`, which is an adjusted copy of [Makefile_template](Makefile_template)
