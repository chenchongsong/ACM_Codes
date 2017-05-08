def main_quare(n):
    tmp = (n*n+n)**2 + n*(n+1)*(2*n+1) + n*(n+1)
    return tmp//12

def new_column(n):
    return n + (n-1)*n*(n+1)//2 - n*(n+1)*(2*n+1)//6 + n*n

infile = open("A-large-practice.in", "r")
with open("ans.txt", "w") as outfile:
    for tc in range(int(infile.readline())):
        #rc = infile.read()
        r, c = map(int, infile.readline().split())
        #prototype: list/tuple/...= map(function_name, list)
        if (c < r):
            r, c = c, r
        r = r-1
        c = c-1
        ans = main_quare(r) + (c-r)*new_column(r) #r = min(r, c)
        outfile.write("Case #" + str(tc+1) + ": ")
        outfile.write(str(ans % 1000000007)+"\n")

