two_power = [1]
for i in range(1, 10001):
    two_power.append( two_power[i-1]*2 )

f = [0,1]
for i in range(1,200):
    for j in range(i+1):
        f.append(f[len(f)-1]+two_power[i])
while True:
    try: n = input()
    except EOFError: break
    print(f[int(n)])
