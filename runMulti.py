#!/usr/bin/python3

import subprocess
import random

for i in range(2000):
    la = str(random.randrange(1, 10))
    lg = str(random.randrange(1, 10))
    ra = str(random.randrange(1, 10))
    rg = str(random.randrange(1, 10))

    # print(lg, la, rg, ra)
    x = f"./runSimulations {la} {lg} {ra} {rg} >> out.txt&"
    print(x)
    subprocess.run([x], shell=True)