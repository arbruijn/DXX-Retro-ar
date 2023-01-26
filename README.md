DXX Retro-ar
=========

Latest versions
---------------

* D1X-Retro-ar - 1.4.X6-ar3
* D2X-Retro-ar - 1.4.X3-ar3

Changelog
---------

<h3>-ar3 - 1/26/2023</h3>

* Support for global custom textures in png format
* Support for global custom models in ase format (D1 only)
* Reduced Flash Effects option
* Saves screenshots as png files
* Fix teleporting homing missle (https://youtu.be/2dP51znGh7o)
* Fix ship wing color shape in random texture after certain levels
* Experimental Homing Speed Drop on Turn option (normalize quick)
* Experimental Homing Update Rate up to 30

<h3>-ar2 - 10/26/2022</h3>

* Experimental Homing Update Rate option
* Allow Packets per second up to 40
* Allow weapon duplication up to x8

<h3>-ar1 - 10/23/2022</h3>

* Added Classic Depth Ordering for classic explosions
* Support loading Rebirth save games
* Fix flickering with headlight on
* Fix ship brightness in endlevel terrain
* Various compilation fixes

<h3>1.4X6 - 1/16/2018</h3>

This experimental release is for D1X-Retro only.

* Coop
* * Don't respawn robots in coop.
* Demos
* * Fix rewind bug where rewinding through a frame with multiple damage sources would show damage and energy incorrectly.
* Mac
* * Switch from XCode to scons for building.  Note: message box tech is disabled for now, crashes will only display to the terminal or the log.  To see them, run Descent from Terminal using the command `./d1x-retro-1.4.X6.app/Contents/MacOS/d1x-rebirth`
* Observer
* * Don't lock to player 1's view while observing in coop.
* * Observers no longer disconnected when other observers connect or disconnect.
* * Observers no longer see themselves connect as an unpatched client when someone else connects to the game.
* * Observers will now be properly told that they can't observe a game that hasn't yet started.
* * You can now observe players directly in first and third person view.  Use Ctrl+1 through Ctrl+8 to observe players 1 through 8.  Use Ctrl+9 and Ctrol+0 to cycle back and forth through the connected players and free observing.  Use Ctrl+- for first person view and Ctrl+= for third person view.
* * Added the above options to the multiplayer F1 help menu, and streamlined the menu to only display relevent commands.
* * Documented the /noobs command (kick all observers) in the F1 help menu.
* * Shields and shield changes are now visible to observers.

<h3>1.4X5 and earlier</h3>

* For changes to 1.4X5 and prior, please see the source.
