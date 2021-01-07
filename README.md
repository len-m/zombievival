# Zombievival

Zombievival is a topdown singleplayer zombie-shooter game, coded using SFML. The player owns a weapon, that is used to kill zombies, that spawn in his environment. While doing so he earns money, that can be used to buy upgrades, that improve his abilities. The longer he lives, the higher to score, the harder it gets, due to the zombies becoming stronger.

## Cloning

HTTPS clone:
```bash
git clone https://github.com/len-m/zombievival.git
```

## Compiling

To compile the game, SFML needs to be installed. The folder containing SFML needs to be called `SFML-2.5.1` and it needs to be in the root directory.
The project is compiled using cmake. To build the project create a new directory for the binaries:

```bash
mkdir build
cd build
```

On Windows using MinGW64, the binaries can be generated with:
```bash
cmake -G "MinGW Makefiles" ..
```
Now the game can be compiled:
```bash
cmake --build .
```

For the game to function correctly the folders `pics`, `sounds`, `fonts` and all `.dll` files in the folder `libs` need to be moved to the directory containing the executable.

## License
[MIT](https://choosealicense.com/licenses/mit/)
