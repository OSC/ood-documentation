#! /usr/bin/python3.6

import subprocess

string=subprocess.check_output(["find", ".", "-name", "*.drawio", "-print"])
arr=string.splitlines()
for s in arr:
    sD=s.decode("utf-8")
    subprocess.run(["drawio-batch", sD, sD[22:-7] + ".png"])

