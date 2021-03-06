//
// Created by Ines Benghezal on 05/04/2019.
//


#include "ImageBase.cpp"
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "ImageBase.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    char cNomImgLue[250], cNomImgEcrite[250], nomMasque[250];
    if (argc != 4) {
        printf("Usage: ImageIn.pgm masque.pgm ImageOut.pgm\n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", nomMasque);
    sscanf(argv[3], "%s", cNomImgEcrite);
    
    ImageBase masque;
    masque.load(nomMasque);
    
    ImageBase out(masque.getWidth(), masque.getHeight(), masque.getColor());
    ImageBase imageBase;
    imageBase.load(cNomImgLue);
    
    int imin = imageBase.getHeight(), imax = 0;
    int jmin = imageBase.getWidth(), jmax = 0;
    
    for (int i = 0; i < masque.getHeight(); ++i) {
        for (int j = 0; j < masque.getWidth(); ++j) {
            if (masque[i][j] == 255) {
                if (i < imin) {
                    imin = i;
                } else if (i > imax) {
                    imax = i;
                }
                if (j < jmin) {
                    jmin = j;
                } else if (j > jmax) {
                    jmax = j;
                }
            }
        }
    }
    
    for (int i = 0; i < imageBase.getHeight(); ++i) {
        for (int j = 0; j < imageBase.getWidth(); ++j) {
            if (masque[i][j] == 255) {
                double distMin = imageBase.getWidth();
                int ppvI = i, ppvJ = j;
                for (int k = imin; k < imax; ++k) {
                    for (int l = jmin - 10; l < jmax + 10; ++l) {
                        if (masque[k][l] == 0) {
                            int x = abs(j - l);
                            int y = abs(i - k);
                            double dist = sqrt(pow(x, 2) + pow(y, 2));
                            if (dist < distMin) {
                                distMin = dist;
                                ppvI = k;
                                ppvJ = l;
                            }
                        }
                    }
                }
                out[i][j] = imageBase[ppvI][ppvJ];
            } else {
                out[i][j] = imageBase[i][j];
            }
        }
    }
    out.save(cNomImgEcrite);
}
