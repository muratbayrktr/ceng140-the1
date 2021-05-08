from math import cos,sin,pi

to = [0,3]

L = [
    [0,0,1],
    [0,1,2],
    [1,0,3],
    [1,1,4]
]


def rotate_point(direction,degree,L):
    if direction == 'R':
        degree = 360-degree

    rad = degree*pi/180

    for i in range(len(L)):
        x = L[i][0]
        y = L[i][1]
        L[i][0] = round((x)*cos(rad) - (y)*sin(rad)) 
        L[i][1] = round((x)*sin(rad) + (y)*cos(rad)) + 1

        
    return L

rotate_point('R',90,L)

for i in L:
    print(i)