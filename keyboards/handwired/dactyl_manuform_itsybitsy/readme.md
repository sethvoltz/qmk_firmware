# Dactyl Manuform (4x5, 5x6, 5x7, 6x6)

the [Dactyl-Manuform](https://github.com/tshort/dactyl-keyboard) is a split curved keyboard based on the design of [adereth dactyl](https://github.com/adereth/dactyl-keyboard) and thumb cluster design of the [manuform](https://geekhack.org/index.php?topic=46015.0) keyboard, the hardware is similar to the let's split keyboard. all information needed for making one is in the first link. ![Imgur](https://i.imgur.com/7y0Vbyd.jpg)

## Adafruit ItsyBitsy

This variant uses the Adafruit ItsyBitsy 32u4 (5v, 16Mhz) board. Because the pinout varies from the Sparkfun/generic Pro Micro pinout, here is a wiring table.

```plain
                     ItsyBitsy

               Rst o  [ USB ]  o Bat
   RJ11 3       5v o           o Gnd
               Arf o           o USB
   RJ11 4      Gnd o           o 13     C7
    Row 1  F7   A0 o           o 12     D6  Col 1
    Row 2  F6   A1 o           o 11     B7  Col 2
    Row 3  F5   A2 o           o 10     B6  Col 3
    Row 4  F4   A3 o           o 9      B5  Col 4
    Row 5  F1   A4 o           o 7      E6  Col 5
    Row 6  F0   A5 o           o 5      C6  Col 6
           B1  SCK o           o 3 SCL  D0  RJ11 1
   RGB DI  B2   MO o           o 2 SDA  D1  RJ11 2
           B3   MI o           o 1 TX   D3
                3v o o o o o o o 0 RX   D2
                     E G 8 6 4
                     n n B D D
                       d 4 7 4
```

## First Time Setup

Download or clone the `qmk_firmware` repo and navigate to its top level directory. Once your build environment is setup, you'll be able to generate the default .hex using:

Depending on your Layout chose one of the follwing commands:

```bash
$ make handwired/dactyl_manuform/YOUR_LAYOUT:YOUR_KEYMAP_NAME
```

example:

```bash
$ make handwired/dactyl_manuform/4x5:default
```

If everything worked correctly you will see a file:

```plain
dactyl_manuform_YOUR_LAYOUT_YOUR_KEYMAP_NAME.hex
```

For more information on customizing keymaps, take a look at the primary documentation for [Customizing Your Keymap](/docs/faq_keymap.md) in the main readme.md.

## Required Hardware

Apart from diodes and key switches for the keyboard matrix in each half, you will need:

* 2 Arduino Pro Micros. You can find these on AliExpress for ≈3.50USD each.
* 2 RJ9 sockets and 1 RJ9 cable, or 2 RJ11 sockets and 1 RJ11 cable
* 4 4.7kΩ pull-up resistors

## Optional Hardware

A speaker can be hooked-up to either side to the `5` (`C6`) pin and `GND`, and turned on via `AUDIO_ENABLE`.

## Wiring

The 3 wires of the TRS/TRRS cable need to connect GND, VCC, and digital pin 3 (i.e. PD0 on the ATmega32u4) between the two Pro Micros.

Next, wire your key matrix to any of the remaining 17 IO pins of the pro micro and modify the `matrix.c` accordingly.

The wiring for serial:

![serial wiring](https://i.imgur.com/C3D1GAQ.png)

The wiring for i2c:

![i2c wiring](https://i.imgur.com/Hbzhc6E.png)

The pull-up resistors may be placed on either half. It is also possible to use 4 resistors and have the pull-ups in both halves, but this is unnecessary in simple use cases.

You can change your configuration between serial and i2c by modifying your `config.h` file.

## Notes on Software Configuration

the keymaps in here are for the 4x5 layout of the keyboard only.

## Flashing

To flash your firmware take a look at: [Flashing Instructions and Bootloader Information](https://docs.qmk.fm/#/flashing)

## Choosing which board to plug the USB cable into (choosing Master)

Because the two boards are identical, the firmware has logic to differentiate the left and right board.

It uses two strategies to figure things out: looking at the EEPROM (memory on the chip) or looking if the current board has the usb cable.

The EEPROM approach requires additional setup (flashing the eeprom) but allows you to swap the usb cable to either side.

The USB cable approach is easier to setup and if you just want the usb cable on the left board, you do not need to do anything extra.

### Setting the left hand as master

If you always plug the usb cable into the left board, nothing extra is needed as this is the default. Comment out `EE_HANDS` and comment out `I2C_MASTER_RIGHT` or `MASTER_RIGHT` if for some reason it was set.

### Setting the right hand as master

If you always plug the usb cable into the right board, add an extra flag to your `config.h`

```c
 #define MASTER_RIGHT
```

### Setting EE_hands to use either hands as master

If you define `EE_HANDS` in your `config.h`, you will need to set the EEPROM for the left and right halves.

The EEPROM is used to store whether the half is left handed or right handed. This makes it so that the same firmware file will run on both hands instead of having to flash left and right handed versions of the firmware to each half. To flash the EEPROM file for the left half run:

```bash
$ make handwired/dactyl_promicro:default:avrdude-split-left
$ make handwired/dactyl_promicro:default:avrdude-split-right
```

After you have flashed the EEPROM, you then need to set `EE_HANDS` in your config.h, rebuild the hex files and reflash.

Note that you need to program both halves, but you have the option of using different keymaps for each half. You could program the left half with a QWERTY layout and the right half with a Colemak layout using bootmagic's default layout option. Then if you connect the left half to a computer by USB the keyboard will use QWERTY and Colemak when the right half is connected.

## Notes on Using Pro Micro 3.3V

Do update the `F_CPU` parameter in `rules.mk` to `8000000` which reflects the frequency on the 3.3V board.

Also, if the slave board is producing weird characters in certain columns, update the following line in `matrix.c` to the following:

```c
// wait_us(30);  // without this wait read unstable value.
wait_us(300);  // without this wait read unstable value.
```
