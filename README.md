# Pseudogoogle

## Requirements
- libcurl
```bash
$ sudo apt install libcurl4-openssl-dev
```
- gumbo
```bash
$ sudo apt install libgumbo-dev
```

## Installation

```bash
$ git clone https://gitlab.cs.put.poznan.pl/inf141240/pseudogoogle.git
$ cd pseudogoogle/server
$ make
```

## Running server

In `server` directory run e.g.:

```bash
$ ./pseudogoogle_server --url=https://example.com
```

You can learn more about parameters by running 

```bash
$ ./pseudogoogle --help
```