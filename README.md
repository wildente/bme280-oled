description
===========

fetch temperature, humidity and pressure from a bme280 sensor and display them on a ssd1306 compatible oled.

tools
=====

- platformio


development setup
=================

install platformio core. you can use other programming tools, but i like this one, because i like to use
*pio* together with *vim*.


never run this as root!

    pip2 install -U platformio

    git clone https://github.com/wildente/bme280-oled.git
    cd bme280-oled


search you board. i have an wemos d1 mini:

    pio boards wemos
    pio init --board d1_mini


install libraries from required_libraries.txt:

    pio lib install 13 135 901



compile and upload
==================

have a look at the code and uncomment "#define DEBUG" if necessary.

    pio run
    pio run -t upload

