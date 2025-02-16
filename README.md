# Touhou Danmakufu ph3.5 0.5 ~ Netplay Edition
This version of Danmakufu is made for implementing Netplay in it; see WishMakers' repository for a link to the original download. <b>The master branch version of this repo is completely backwards compatible with ph3 (and has the original readme). This branch contains functions that are not in original PH3. If something doesn't work as expected, refer to the contact info in Woo (the repo original to this one).</b> Most of the stuff there also applies here.

Changelog:

###### [0.5]
 * Function naming simplified
 	- "TCP" removed from the Data functions

###### [0.4]
 * Changed ReceiveTCPData
 	- The function now returns saved data instead of nothing, allowing the example script to actually work
 * Added a functional logging system
 	- Functions will write what happens to the WindowLog

###### [0.3]
 * Changed ReceiveTCPData
	- The function now deletes saved data before receiving instead of after
 * Fixed the data saving system
 	- SendTCPData now actually returns saved data instead of nothing

###### [0.2]
 * Changed RunNetplay's first argument to "server", bool
	- Removed UDP support to focus on TCP

###### [0.1]
 * Added RunNetplay(mode, port, address)
	- Runs the Netplay module in TCP server, client or UDP client mode, with the appropriate port and address
 * Added ReceiveTCPData(delete)
	- Receives data from the other person in the connection, deleting the data received or not
 * Added SendTCPData(data, direct)
	- Sends data to the other person in the connection, either custom or directly any saved data

## Requirements (for compiling)
 * zlib
</br>Best and recommended way to obtain it is to use [vcpkg](https://github.com/Microsoft/vcpkg) C++ Library Manager.
 * sfml
</br>Get it here: https://sfml-dev.org
</br>Also deserves credit because it was used to implement netplay in the first place.

## Known Issues
 * Wine 4.12.1 (confirmed on macOS at least) suffers some scaling problems with the window size, being 9 pixels too wide and 7 pixels too tall.  This causes some nasty scaling on in-game assets, possibly a result of old Windows size calls not being 100% compatible with Wine releases.
 * The exe will crash when trying to load a sound file that is both: not 1411kbs and is stereo

## Special Thanks
WishMakers - for making Danmakufu Woo and helping me out

## Contributions
This is an outdated version of [DNH-V](https://github.com/gmestanley/DNH-V), and as such it's no longer in active development. If you want to see Netplay in Danmakufu, check out that project instead, as the same features were carried over to it.

## New Features Branch
Although this project was forked from newfeatures, this branch and its releases still exist for people who don't want to have the new features bundled in (for whatever reason you may have). If you don't know which to use, just use this one.

## License
zlib library has its own license, please check zlib.h in the repo for that information.</br></br>
(quoted from James7132's repo of the original source, maintaining the same license.) </br>This code is licensed under the NYSL (Niru nari Yaku nari Suki ni shiro License'). Main translated points:

 * "No warranty" disclaimer is explicitly included.
 * Modified version of the software MUST be distributed under the responsibility of the distributer.
 * Official version is written in Japanese.
