# sm64 blj trainer
![Example screenshot](doc/sm64-blj-trainer.png)

**sm64 blj trainer** is a Nintendo 64 ROM for practicing consistent frame-perfect bljs in Super Mario 64. This ROM is a n64 port of xandrey's practice tool. The GUI is also heavily inspired by [wermi's controller test ROM (mimi)](https://github.com/wermipls/mimi)

## Download
Latest version of the ROM can be found [here](https://github.com/rollercobester/sm64-blj-trainer/releases).

## Basic controls
In the main menu:
* D-Pad - select option
* A - confirm selection

On the about/help screen:
* B - return to main menu

On the practice tool screen:
* A - record blj frame
* B - return to main menu

Additional informations on usage can be found in the help screen built into the ROM.

## Building
If you would like to build the ROM yourself, you will need to have [libdragon](https://libdragon.dev/) set up. 

Clone the repository (including submodules) and navigate to the directory:
```
git clone --recurse-submodules https://github.com/rollercobester/sm64-blj-trainer/
cd sm64-blj-trainer
```

For initial build:
```
libdragon init
libdragon make
```

After that, the ROM should be possible to compile with just `libdragon make`.

## Credits
* xandrey - initial python code
* coby - porting to n64

Special thanks to xandrey, wermi, kolunio, LFoxyIsBlue, GTM, and GreenSuigi.

### 3rd party assets
* [Enter Command font by Font End Dev](https://fontenddev.com/fonts/enter-command/), licensed under CC BY 4.0

## License
MIT
