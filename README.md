# dll inventory system

An example of using dynamically linked libraries to persist inventory data!

## Requirements

You need to have `g++` installed, otherwise the inventory can't be stored when you make changes.

## Features

- Store all of your inventory data in .so files
- Add or remove items at will (you only pay the compile cost when you close the inventory)
- Blazingly fast (g++ is pretty fast I think)
- Only mildly exploitable (production ready)

## Compiling

```
cmake -S . -B builds && cmake --build builds
```

Then run with

```
./builds/inventory
```

## Example Parsing Failure

You can achieve arbitrary code execution under this scheme as well! As a proof of concept, tell the program to store the following.

```
itemName"};}auto l=[](){std::puts("!!!");};struct X{ X(){l();} }; static X x;extern "C"{ std::array<std::string, 1> a{"a
```

When the library is loaded again, "!!!" will be sent to the terminal.
