
# ECM2433 - The C family

## Contents
 1. Compilation instructions
 2. How to run
 3. Other stuff

### 1. Compilation instructions

Compiling this program is pretty simple, as it uses `make` in order to compile, and link all of the source code, and the
libraries.

So please ensure you have the standard build tools installed on your system.
On a Debian distro of linux, this can be done using the command:

`$ sudo apt-get install build-essential`

Once you have this all installed (chances are, it already is), you can crack on with compiling this script.

I have provided (as per the spec), a simple bash script that will do this for you, simply run:

`$ ./compileSim`

From the root directory.
This will generate an executable library called `runSimulation`.

### 2. How to run

To run the program, simply put:

`$ ./runSimulations {LA} {LG} {RA} {RG}`

Substituting:
 - LA: Left arrival rate
 - LG: Left green time
 - RA: Right arrival rate
 - RG: Right green time

Where the arrival rate is a positive number, greater than 0, and less than infinity (see the write-up for an explanation).
The higher this is, the more likely a car is to arrive.

And the green time is the number of iterations before the lights change, make this below 500.

### 3. Other stuff

If you want some example data, `out.csv` contains some that I generated using `runMulti.py`
Feel free to mess around with the numbers in the python program, just beware that it detaches all of the processes,
so you will have to kill them all yourself, if they fail to yeild any results.

To kill them all run:

`$ killall ./runSimulations`
