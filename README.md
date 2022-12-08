# OffensiveSecurity_CTF_assignment

## ROT_KEY.c

### Compile
```sh
gcc rot_key.c -o rot_key
```

#### Running

##### Replicating the behaviour of the given executable
```sh
./rot_key 
```
or
```sh
./rot_key authenticate
```


##### Printing the secret code to use with your PIC
```sh
./rot_key crack
```


## test_script.py

This script was writtent in order to test all the possible PICs with respect to my intuition: it is a common Caesar Cipher whose key is the sum of PIC's digits.

### Running

```sh
python3.10 test_script.py
```

## Author
Campa Luca
