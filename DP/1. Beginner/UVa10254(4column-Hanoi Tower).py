# F(n)=min{ 2*F(n-r)+2^r-1 }, (1≤r≤n)
# Therefore, F(n)=min{ (n-(r^2-r+2)/2)*2^r+1 }
# Actually, r=(sqrt(8*n+1)-1)/2
def f(x):
    r = int( (math.sqrt(8*x+1)-1) /2 )
    return int( (x-(r**2-r+2)/2)*two_power[r]+1 )

import math
two_power = [1]
for i in range(1, 10001):
    two_power.append( two_power[i-1]*2 )
while True:
    try:
        n = input()
    except EOFError:
        break
    n = int(n)
    print(f(n))
