### pmd-sky-dungeon-data-extractor
Quick tool to scrape dungeon data from the pmd2 binaries.

### !! This data is scraped mostly blindly and is not guaranteed to be correct !!
Also, the format might change or I might add or correct the data at any time. If you need this data, you might want to copy the included JSON output file or require a specific commit for your own project.

Currently the demo dungeons and dojo dungeons are not in the JSON.

### How do I interpret this JSON data
See https://github.com/UsernameFodder/pmdsky-debug or another pmd2 rom hacking resource.

### Compiling
You shouldn't need to do this if you just want to use the data, but it might be useful to tweak the output.

Compiling requires the nlohmann JSON C++ library (see https://github.com/nlohmann/json). On Ubuntu, the packages is called nlohmann-json3-dev. CMake should take care of the rest.

### Usage
Just run it.

The executable expects the files arm9.bin and mappa_s.bin in the same folder to extract data from. You can acquire these by using an unpacker like DSLazy on the game ROM, but I won't distribute the files myself.

### Reverse engineering notes
(All addresses are for the Sky EU rom.)
When generating a new floor, the game loads that floors generation parameters into a struct in memory at adress 0x021E2D26. There are also two bytes before that which  I didn't look into since I didn't need them, but they are not part of the floor data in mappa_s.bin.

The code that copies the data into said memory location starts around 0x022E7AF4.
