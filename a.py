import math
a = int(input(3))
b = int(input())
c = int(input())
s = (a+b+c)/2
area = math.sqrt(s*(s-a)*(s-b)*(s-c))
print("三角形的边长：",a,b,c,end='')
print("三角形的面积：",area)