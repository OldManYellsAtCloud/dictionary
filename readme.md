Dictionary application

This is for my own use, and I doubt that anyone else would find it useful, but here are some thoughts:

- It is a simple offline de-en/en-de dictionary, written in C++, using Qt6/QML for the UI.
- It uses dictionary files from [dict.cc](https://dict.cc) - that project graciously makes their dictionary files available for free, however they don't allow their redistribution. To use this application, you will need to either supply your own dictionary files, or get your own set from dict.cc (which is recommended).
- The application expects a configuration file in `/etc` folder, having the same name as the executable, with `.cfg` extension, e.g. `dictionary.cfg`. The file is an `.ini` style config, with the following content:
```
[language]
; path to english-german dictionary file
en=/usr/share/wherever/the/file/is/en-de.txt
; path to german-english dictionary file
de=/usr/share/wherever/the/file/is/de-en.txt

[general]
; maximum number of potential matches to fetch/display at a time
numberOfResults=20
```

My usecase was to run this on my own system - it may or may not work for your usecase.

