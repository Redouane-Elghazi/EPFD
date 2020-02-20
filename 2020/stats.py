#!/usr/bin/env python3

import numpy as np

librariesBooks = []
librariesDelay = []
librariesShipment = []
books = []

B, L, D = map(int, input().strip().split())

books = list(map(int, input().strip().split()))

for l in range(L):
    tmp_size, tmp_delay, tmp_ship = map(int, input().strip().split())
    
    librariesDelay.append(tmp_delay);
    librariesShipment.append(tmp_ship);
    librariesBooks.append(list(map(int, input().strip().split())))
