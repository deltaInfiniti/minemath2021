(if you're reading this in notepad, format->word wrap)
SPELLCHECK ME
           ********  Welcome to ValSuite. Neopets Botting re-Imagined.**********

terms: this program is a bot for neopets.com.  If you use this program your account(s) may be frozen.  This program can create noticeable web traffic, and if missused can be detrimental to computer servers. You accept all responcibility for the use of this program.

Password information:
ValSuite does not save your Master password.  If you forget/lose your password, there is no way to recover it, or any of your userdata. 

You do not need to use an extremely complicated password, though it does increase security. ValSuite uses a proprietary, high security encryption system with a proprietary cryptohashing algorythm. The sources distributed with ValSuite do not contain the private version of ValCrypt, and therefor cannot be used to decrypt your user files, even given the proper password.
ValSuite DOES save your individual game account passwords locally, behind said encryption based on your master password.

Usage tracking:
ValSuite does not track you. Optional runtracking will be implimented in the future (notifying my server of what functions are being used by the userbase so I can pay more attention to that kind of activity)


redistrobution: 
ValSuite is a free and opensource project by me, valseedian. The source code is available at -link removed- and newer versions can be requested directly.  If you need any help compiling your own version, Contact me for assistance. You may copy, alter and or distribute the source code and program as you see fit, under the single clause that you clearly represent it is produced by you, from my sources.   


That's all the technical data.. Notes are found below. Read if you'd like.

Features list: [x] completed
Version Alpha0.0.1
[x]full hypervisor and safe local storage
[x]full forms window manager
[] 3p1k username manager
  []pins
  []proxies
[] Flash game score sending script (maybe not so much if flash is dieing soon. glad I didn't spend long here
[] MSAB -- not much work left here
[] usab -- some work to do on easy version
[] username gatherer -- for usab
[] functional scripts -- faerie quests, dailies, etc
[] games autoplayers - neggsweeper for sure
[] ValScheduler for ensuring each selected event gets a proper session before moving on- legitimizer



ValSuite is a passion project. I've been a programmer for nearly 20 years now, and I did neopets programs for a long time.  I lost all of my sources in 2013, and stopped doing neopets programs alltogether.  2020 has been a long year. A few months into The Event, I began programming again.  I got my hands on my old headers- Not maincode, but it's a start, and a copy of my scripting engine and my minesweeper autoplaying bot sources.  

This story is continued on -link removed-

long story short, I decided to start refreshing my other old programs.  But this time I needed to do better than using consoles.  So I needed a forms designer that could be used by valscript.  I didn't know much about the regular windows forms then, but I did know a ton about click events and I had my own graphics drawing library, so I decided to make my own from the ground up.
That mindset lead to ValWindowManager and it's dependencies
