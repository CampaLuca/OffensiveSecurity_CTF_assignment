#!/bin/bash python3
import subprocess,os


# encrypt offsec with given key length
def encrypt(key):
    plaintext = "offsec"

    ciphertext = ""
    for c in plaintext:
        ciphertext = ciphertext + chr(((ord(c) - 0x61 + key) % 0x1a) + 0x61)

    return ciphertext


def main():
    for pic in range(0,10000):
        string_pic = f"{pic:04}"
        sum_of_digits = 0
        for digit in string_pic:
            sum_of_digits += int(digit)

        key = sum_of_digits % 0x1a

        secret = encrypt(key)

        payload = string_pic + "\n" + secret + "\n"

        p = os.popen("echo \""+payload+"\" | ./auth-challenge-elf").read()
        #print(p)
        if "flag" not in p:
            print("ok")

if __name__ == '__main__':
    main()