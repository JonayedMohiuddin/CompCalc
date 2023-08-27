#
# Created by hakim15 on 8/24/23.
#


# this is just a clumsy python script to check a possible assignment
# run python check.py INPUT_FILE OUTPUT_FILE

# you can use tqdm as a progress bar
# from tqdm import tqdm

import sys

vals = dict()


def tilde(x):
    if x.find('~') == -1:
        return '~'+x
    return x


with open(sys.argv[2], 'r') as file:
    ls = file.readlines()
    for l in ls:
        l = l.strip().split()
        x = l[0]
        if l[1] == 'True' or l[1] == 'true':
            vals[x] = True
            vals[tilde(x)] = False
        else:
            vals[x] = False
            vals[tilde(x)] = True


with open(sys.argv[1], 'r') as file:
    n = int(file.readline().strip())
    for i in range(n):
        l = file.readline().strip().split()
        val = False
        for t in l:
            val = val or vals[t]
        if not val:
            print("Line", i+2, ": Invalid --- ", l)
            sys.exit(1)

print(sys.argv, " --- all good")


