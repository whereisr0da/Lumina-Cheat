![](Resources/logo.png)



![](Resources/preview_0.png)

# What is it ?

This is the CSGO cheat I'm coding since 2018.

# Why ?

I've coded this because there are too many cheaters in this game. I'm angry that I can't do anything against cheaters with the vanila CSGO. So I'm cheating ONLY against cheaters.

# Is it detectable ?

Well.

The cheat by itself (the file, the code) is not "identifiable" because of code mutation. I'm using VMP mutation for every functions I made, and the compilation doesn't split that much the code regarding the mutation (at least with my current configuration).

So if you use it mutated on VAC protected servers, Steam anti cheat will not be able to find any known patterns because of code mutation. Even if VAC detect the module and send it to Valve's servers to "extract" sigatures, next time the cheat is compiled, its code signature will completly change (my functions). So VAC cannot identify the cheat by a code signature of my features. However, I use public code that could be flagged by VAC (JsonCpp, ZGUI, ...), but those codes are commonly used by legit softwares. And if VAC flag them, they will flag most of the overlay software too, so they don't do it. 

So let's summarize, the code signature is not detectable, is the cheat still detectable then ? YES

The first vector could be the DLL injection. In my case the CSGO process load by itself the crashhandler.dll, so the module is loaded before the installation of LoadLibrary and other hooks. But if the injection process is spotted by CSGO process, you will be VAC.

The second is to consider the "pattern" detection of the cheat. For exemple if VAC is now able to detect a feature of the cheat, no matter its implementation. You will be VAC, as well as skeet users when double tap was detected by CSGO. So maybe tomorow, the Faststop feature could be detected server side. 

I could continue my explanation for hours (string, data...) but I think you get the idea.

# Why do I release this then ?

Like I explained earlier, the point of being not detected regarding the code is highly liked to knowledge of VAC about it. So, more people use it, more chance that it's "detected", even if I use code mutation. 

But I've spend a lot of time working on this game, and I think it's now time to do release it as I'm not playing that much anymore.

# How to use ?

Place the crashhandler.dll file Steam's root folder. CSGO will load it before applying the LoadLibrary hook.

# Features

Like I said, it's a legit cheat, so features are meant to be hidden regarding overwatch. But it's depending of your own gameplay.

- Chams
- Glow
- Skin Changer (two slots, T and CT)
    - Weapon (paint, stickers, ...) 
    - Knife 
    - Local Model
    - Team Model
- ESP
    - Show only if dead
    - Box
    - Name
    - Life
    - Indicators (flash, scope, has defuser, has bomb, planting, defusing, ...)
- Grenade Prediction
- Radar
- Misc
  - My Spread Circle + Crosshair (not the classic filled cirle)
  - Hitmarker + Sound
  - Spectator List
  - Fast Stop
  - Silent Walk
  - Flash Timer

# About the code

I made the cheat optimized, but there is one thing that is not looking good in all this project, the UI.

I started to made the UI from raw, but at the end I didn't want to put too much effort into it. So I used the zgui framework to handle it, and I didn't took the time to modify the gui, buttons and stuff. So the menu (the button and UI) are pretty huggly, but I prefer to work on features instead of loosing time on this.

It's why I don't provide screenshots of the menu.

# Credit

- Oneshot
- JsonCpp http://jsoncpp.sourceforge.net/
- zxvnme (zgui)
- coders from pandoracheats.pw
- Ferenc Deak, Sebastien Andrivet https://github.com/andrivet/ADVobfuscator
- Justas Masiulis https://github.com/JustasMasiulis/lazy_importer, https://github.com/JustasMasiulis/xorstr