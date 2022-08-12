# hangman

`hangman` is a siimple hangman game in C. Words / phrases to be used in the
game must be placed in a FILE. Currently, `hangman` reads and serves FILE's
content linearly (not randomly).

## Usage

```
$ hangman FILE
```

Example:

```
$ hangman exampleguessfile.txt
```

or

```
$ hangman exampledict.txt
```

## Building

```
$ cd /path/to/intended/repo/dir
$ git clone https://github.com/richiesuper/hangman
$ cd hangman
$ make <TARGET>
```

## Source Code Viewing

Use tabstop of size 4 to view the code as I intended it to be.
