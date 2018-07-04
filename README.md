Don't explode
==

A hardware implementation of the game "Keep talking and nobody explodes".

How it works
==
Each module is comprised of some harware that can communicate via i2c.

Arduino is currently the chosen plattform for the implemented modules.

Project structure
==

```
├── README.md              -> This file
├── libraries              -> useful libraries for modules
│   ├── BombCom            -> i2c communication library
│   │   ├── CMakeLists.txt
│   │   ├── lib
│   │   ├── platformio.ini
│   │   ├── src
│   │   └── test
│   └── RandomSeed         -> simple library for better random behavior
│       ├── CMakeLists.txt
│       ├── lib
│       ├── platformio.ini
│       ├── src
│       └── test
└── wires                  -> Software for the wires module
    ├── CMakeLists.txt
    ├── lib
    │   ├── WiresModule
    │   ├── WiresPuzzle
    │   └── readme.txt
    ├── platformio.ini
    ├── src
    │   └── main.cpp
    └── test
        ├── test_embedded
        └── test_native
```

Adding a module
==
TODO