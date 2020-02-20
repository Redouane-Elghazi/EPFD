#!/usr/bin/env python3

import numpy as np
import sys
import IPython
import matplotlib.pyplot as plt

with open(sys.argv[1]) as in_file:
    librariesBooks = []
    librariesSignup = []
    librariesShipment = []
    score = []

    B, L, D = map(int, in_file.readline().strip().split())

    score = np.array(list(map(int, in_file.readline().strip().split())))

    for l in range(L):
        tmp_size, tmp_delay, tmp_ship = map(int, in_file.readline().strip().split())
        
        librariesSignup.append(tmp_delay);
        librariesShipment.append(tmp_ship);
        librariesBooks.append(list(map(int, in_file.readline().strip().split())))

    ordered_books = np.argsort(score)

    libs_per_book = [set() for _ in range(B)]
    for i, lib in enumerate(librariesBooks):
        for book in lib:
            libs_per_book[book].add(i)

    nb_libs_per_book = np.array([len(libs) for libs in libs_per_book])
    
    
    score_per_nb_shared_lib = np.zeros(max(nb_libs_per_book)+1)
    for book, nb_libs in enumerate(nb_libs_per_book):
        score_per_nb_shared_lib[nb_libs] += score[book]
    
    max_score = sum(score[nb_libs_per_book > 0])

    uniq_per_lib = [set() for _ in range(L)]
    for book, libs in enumerate(libs_per_book):
        if len(libs)==1:
            uniq_per_lib[list(libs)[0]].add(book)

    uniq_ratio_per_lib = [len(books)/len(librariesBooks[i]) for i, books in enumerate(uniq_per_lib)]
    
    uniq_score_ratio_per_lib = [sum(score[book] for book in books)/sum(score[book] for book in librariesBooks[i]) for i, books in enumerate(uniq_per_lib)]
    
    score_from_uniq = sum(score[nb_libs_per_book == 1])
    
    def plot_hist_nb_libs():
        plt.subplot(2,1,1)
        plt.hist(nb_libs_per_book)
        plt.subplot(2,1,2)
        plt.plot(score_per_nb_shared_lib)
        plt.show()
    
    def plot_hist_nb_uniq():
        plt.subplot(2,1,1)
        plt.hist(uniq_ratio_per_lib)
        plt.subplot(2,1,2)
        plt.hist(uniq_score_ratio_per_lib)
        plt.show()
    
    print('total score books present', max_score)
    print('Score from uniq', score_from_uniq)
    plot_hist_nb_libs()
    plot_hist_nb_uniq()
    IPython.embed()










