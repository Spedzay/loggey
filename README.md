# 📚 Loggey
[![Actions Status](https://github.com/spedzay/loggey/workflows/CMake/badge.svg)](https://github.com/spedzay/loggey/actions)
[![CodeFactor](https://www.codefactor.io/repository/github/spedzay/loggey/badge)](https://www.codefactor.io/repository/github/spedzay/loggey)

A cross platform C++17 Logging library
for logging output to the terminal/console(windows)

## How to use? ##

Just `#include "loggey.hpp"` Into your project and compile with C++17
Tested Compilers: gcc, msvc clang-cl, mingw(had issues with inline variables for me)

## Loggey Documentation

```c
loggey::logType ALERT = { loggey::colors::red,
	"Alert", loggey::logTypeFlags::addPlus };
```
This will define a logType called ALERT thats prefix is "Alert" and is red.
We also add [+] in front of it using the flag logTypeFlags::addPlus

```c
log(ALERT, "Loggey, the single header C++17 logging library");
```
Now lets log some text! 
the log function is from the loggey:: namespace, 
It takes in a logType reference and a const std::string& to log.

You may also change colors for text defaults in the loggey.hpp file (will change how you can modify colors and settings)
find the loggey_settings namespace and change any of the fields to your liking!

logTypes and loggey_settings can be modified on the fly as the program runs, if you wish to change a logType's flags or
change the text color to green to look nicer, you can do so!

## License 

Check the LICENSE file in this github repository.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change. 

## Security

Check the SECURITY file in this github repository. 
