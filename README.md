# dll inventory system

An example of using dynamically linked libraries to persist inventory data!

## Requirements

You need to have `g++` installed, otherwise the inventory can't be stored when you make changes.

## Features

- Store all of your inventory data in .so files
- Add or remove items at will (you only pay the compile cost when you close the inventory)
- Blazingly fast (g++ is pretty fast I think)

## Compiling

```
cmake -S . -B builds && cmake --build builds
```

Then run with

```
./builds/inventory
```
