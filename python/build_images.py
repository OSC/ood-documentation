#!/usr/bin/env python3.6

import subprocess
from pathlib import Path

string=subprocess.check_output(["find", ".", "-name", "*.drawio", "-print"])
found_files=string.splitlines()
for file in found_files:
    file_decoded=file.decode("utf-8")
    subprocess.run(["drawio-batch", file_decoded, 'source/images/'  + Path(file_decoded).stem + ".png"], check=True)

