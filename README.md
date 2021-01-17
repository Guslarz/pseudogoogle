# Pseudogoogle

(About (PL))[report.pdf]

## Requirements for server
- libcurl
```bash
$ sudo apt install libcurl4-openssl-dev
```
- gumbo
```bash
$ sudo apt install libgumbo-dev
```

## Getting source code

```bash
$ git clone https://gitlab.cs.put.poznan.pl/inf141240/pseudogoogle.git
```

## Server

### Installation

In `server` directory run:

```bash
$ make
```

### Running server

In `server` directory run e.g.:

```bash
$ ./pseudogoogle_server --url=https://example.com
```

You can learn more about parameters by running 

```bash
$ ./pseudogoogle --help
```

## Client

### Installation

In `client` directory run:

```bash
$ mvn install
```

### Running client

Execute jar in `client/target` directory:

```bash
$ java -jar pseudogoogle-client-jar-with-dependecies.jar
```