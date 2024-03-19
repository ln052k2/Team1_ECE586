#!/bin/bash
make
printf "Alpha Predictor"

printf "\nDIST-FP-1\n"
./predictor traces/DIST-FP-1
printf "\nDIST-FP-2\n"
./predictor traces/DIST-FP-2
printf "\nDIST-FP-3\n"
./predictor traces/DIST-FP-3
printf "\nDIST-FP-4\n"
./predictor traces/DIST-FP-4
printf "\nDIST-FP-5\n"
./predictor traces/DIST-FP-5

printf "\nDIST-INT-1\n"
./predictor traces/DIST-INT-1
printf "\nDIST-INT-2\n"
./predictor traces/DIST-INT-2
printf "\nDIST-INT-3\n"
./predictor traces/DIST-INT-3
printf "\nDIST-INT-4\n"
./predictor traces/DIST-INT-4
printf "\nDIST-INT-5\n"
./predictor traces/DIST-INT-5

printf "\nDIST-MM-1\n"
./predictor traces/DIST-MM-1
printf "\nDIST-MM-2\n"
./predictor traces/DIST-MM-2
printf "\nDIST-MM-3\n"
./predictor traces/DIST-MM-3
printf "\nDIST-MM-4\n"
./predictor traces/DIST-MM-4
printf "\nDIST-MM-5\n"
./predictor traces/DIST-MM-5

printf "\nDIST-SERV-1\n"
./predictor traces/DIST-SERV-1
printf "\nDIST-SERV-2\n"
./predictor traces/DIST-SERV-2
printf "\nDIST-SERV-3\n"
./predictor traces/DIST-SERV-3
printf "\nDIST-SERV-4\n"
./predictor traces/DIST-SERV-4
printf "\nDIST-SERV-5\n"
./predictor traces/DIST-SERV-5