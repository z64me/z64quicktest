# z64quicktest

a micro utility to help Zelda64 modders rapidly iterate

created with the help of ChatGPT in under 2 hours (aka it isn't clean/good code)

![showcase.gif](showcase.gif)

## how it works

**z64quicktest** accepts the following:
- path to your emulator of choice
- path to your game (the only [currently?] supported version is oot 1.0 u ntsc)
- which character to play as
- entrance number [see this table](https://wiki.cloudmodding.com/oot/Entrance_Table_(Data))
- time of day (for testing day/night specific things; `0x8000` is midday)
- cutscene (safe to leave as `0x0000` if you aren't testing cutscenes)

when you click the **Play** button, it copies and patches your game and attempts to run it (your original copy is safe!)

this way, testing changes is greatly expedited; no boot screen, no title screen, no file select screen

# special thanks

- this tool was made possible by a patch created by [@Aegiker](https://github.com/Aegiker)
- [@OniHelix](https://github.com/OniHelix) mentioned how long it takes to test changes in a mod he is presently working on (5 minutes each time; that won't do!) and work on this program commenced immediately
