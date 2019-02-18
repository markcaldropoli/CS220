(date && whoami) | tee -a results.txt
make really-clean test 2>&1 | tee -a results.txt
./test 2>&1 | tee -a results.txt
