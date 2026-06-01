
![build-status](https://img.shields.io/badge/build-unknown-lightgrey) ![license](https://img.shields.io/badge/license-MIT-green) ![stars](https://img.shields.io/badge/stars-%E2%98%85-lightgrey)

	____  _  _  _   _   ___   ___ ___  
 |  _ \(_)\|\ \ / / / _ \ / __/ __| 
 | | | | | ' \ V / | (_) | (_ \__ \ 
 |_| |_|_|_||_|\_/   \___/ \___|___/ 

Dino In C — A Tiny Roar from the Terminal
=========================================

Prologue
--------

In the hum of a single-core machine, beneath linear code and patient comments, a small dinosaur stirs. Not drawn by engines nor polished by artists paid in coffee — this dino is stitched from `C`, brewed with a Makefile, and staged to perform inside your terminal.

About the Game
--------------

Dino In C is a handcrafted, minimal runner: reflexes, timing, and the peculiar satisfaction of tiny constraints. It's compact by design, meant to be compiled, played, and hacked within minutes.

Quick Start
-----------

Build and run:

```bash
make
./game
```

Controls
--------

- Jump: `Space` or `Up` arrow
- Exit: `Ctrl+C` (or close the terminal)

ASCII Gameplay Snapshot
----------------------

Imagine a single frame of the chase:

```
Score: 01234

		____         ___    
	 / . .\  ___  /   \   
	(  --- )/___\|     |  
	 `-___-'      \___/   
			 |            ### 
~~~~~~~|~~~~~~~~~~~~~~~~
```

Features
--------

- Tiny, readable C codebase — perfect for learning and tinkering.
- Near-instant build/run loop.
- Asset-light approach: drop in sprites or tweak logic in `main.c`.

Where to Tweak
--------------

- `main.c`: game loop, physics, and input handling.
- `assets/`: sprites, configuration, or mock data.
- `Makefile`: build targets and compiler flags.

Design Notes (Dev Journal)
-------------------------

I wanted a game you could open and understand in one sitting. No libraries, no ceremony—just C logic and a heartbeat. The engine is intentionally small so you can see how the loop breathes, where collisions happen, and how a single variable can make the difference between triumph and a faceplant.

Contributing
------------

Small, focused contributions welcome. Examples:

- Add an obstacle type
- Improve scoring and persistence
- Export a simple replay format

When you send a patch, keep changes readable and atomic.

Changelog
---------

- v0.1 — Initial terminal release: minimal runner, core mechanics, Makefile.

License
-------

This project is licensed under the MIT License. See `LICENSE` for details.

Credits
-------

Made with warm coffee, late-night curiosity, and a stubborn love for tiny games.

Encore
------

Run it, change it, and make the little dinosaur roar louder. If you'd like, I can add a PNG screenshot, CI badges, or an ASCII title graphic variant — tell me which next.

