<p align="center">
    <img src=".github/images/Bestiole.png"
    alt="Moulmerman Logo"
    style="height: 100px">
</p>

# moulmerman
###### 물merman

# Storyline
You are in a city after a mysterious virus kill almost all humans.
You and your new friends build a camp to survive but your new life 
is very annoying, so you tried to find a good game to kill the time. </br>
Luckily you found a game: Bomberman.

# How to play
You can play up to 4 player or AI define the type of the player
in Selection Menu, you can also change the name of the players.
In the game play with these keys:
### Player 1
* Forward `W`
* BackWard `S`
* Left `Q`
* Right `D`
* Bomb `A`
### Player 2
* Forward `T`
* BackWard `G`
* Left `F`
* Right `H`
* Bomb `Y`
### Player 3
* Forward `I`
* BackWard `K`
* Left `J`
* Right `L`
* Bomb `O`
### Player 4
* Forward `ARROW_UP`
* BackWard `ARROW_DOWN`
* Left `ARROW_LEFT`
* Right `ARROW_RIGHT`
* Bomb `Enter`

# How to build the project
You can download the compiled project in [Release](https://github.com/Alvarwow69/moulmerman/releases) section </br>
If you can to build the project follow these steps:
* Download the [ShipWreck Engine](http://api.creative-rift.com/download_sw/libs?platform=windows&v=alpha-0.3-beta_12.rar)
* Unzip the file and put the folder libraries at the root of the repo
* Execute these command
```bash
mkdir build ; cd build
cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=[Debug/Release] ..
cmake --build . --target Moulmerman --config [Debug/Release]
```
* Copy folder `resources` and file `Config.yml` into `out/[Release/Debug]`
* Run the game and enjoy your game