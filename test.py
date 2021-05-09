import sys

my_r = open(f"myoutputs/output2499.txt")
r = open(f"outputs/output2499.txt")


myoutlines = my_r.readlines()
outlines = r.readlines()


for i in range(len(outlines)):
    if myoutlines[i] == outlines[i]:
        print("success")
    else:
        print("-------\nFailed: {} \n Your result : {}\n exptd result: {}\n -----------\n".format(i,myoutlines[i],outlines[i]))