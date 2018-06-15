# simple-config
Small INI parser true to the originals from the 1990's!


* The main goal is to be small. I'm not worried about the number of instructions this may require, since it's really fire-and forget.
* An unordered map stores all the things. If this concerns you, use something else. Maps seem ideal for key/value pairs. 
* Regular expressions are used to parse each line. They seem to have filtered the garbage that I've sent their way (as seem in `simple-config.cpp`)
* Comments get eaten (not preserevd). Run `simple-config.cpp` for proof. I have not tested inline comments.
* Quoted values have no special meaning. They are seen as a regular value, nothing special, and are not removed.
 * Keys that are outside a section (the "default" section) are suppoeted.
 * You may use a colon to separate key and value; the colon is equivalent to the equal sign. That is, the strings "Name: Value" and "Name=Value" have the same meaning.
 * The hash character ("#") is an alternative for the semicolon to start a comment. Trailing comments (i.e. behind a key/value pair on a line) are allowed.
 * Leading and trailing white space around key names and values is ignored.
 * The memory footprint is deterministic. There is no dynamic memory allocation. 

## How to use:

This is a **header-only** library. Just grab `simple-config.h` and include it. Does not interface with files at all, only streams.

- `stringstream`s will work. I use them in the demo (`simple-config.cpp`)
- Reading from a file is as simple as passing a `std::ifstream` to the constructor.

Developed in Visual Studio 2017 as a CMake project.
