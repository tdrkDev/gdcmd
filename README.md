# GDCmd

Geometry Dash in terminal, written on C.

## Building

```sh
sudo dnf install ncurses-devel clang make git
git clone https://github.com/tdrkDev/gdcmd.git
cd gdcmd
sudo make install

# run with
gdcmd 'level file'
```

## Supported platforms

Only hardcore, only linux.

## Creating level

At first, level should be in frame like this:

```
x-----------x
|           |
|           |
|           |
x-----------x
```

And have one-line floor of 'o' symbols, ex:

```
x-----------x
|           |
|           |
|ooooooooooo|
x-----------x
```

Spikes are '!' symbols

Blocks are 'o' symbols

Orbs are coming soon

### Notes
* You can put any other info under level in file (text, your name, etc.)
* Max level size is: 8192 by X, 96 by Y
* Max **parsed by GDCmd** file lines: 128

## TODO

- [ ] Rewrite framebuffer and physics
- [ ] Make gameplay more responsible
- [ ] Ship portal
- [ ] Orbs
- [ ] More fancy graphics
- [ ] For you, reader - have fun
