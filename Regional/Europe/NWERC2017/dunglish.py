n=input()
n=int(n)
sts = input()
sts = sts.split()
wdict={}
wdict_good={}
trans={}
for word in sts:
    wdict[word]=0
    wdict_good[word]=0
    trans[word]=[]

m=input()
m=int(m)
#print(m)
for i in range(m):
    tmpch = input()
    
    #print(tmpch)
    tmpch = tmpch.split()
    if(tmpch[0] in trans):
        trans[tmpch[0]].append(tmpch[1])
        wdict[tmpch[0]]+=1
        if(tmpch[2]=="correct"):
           wdict_good[tmpch[0]]+=1
        
sol=1
goodsol=1
for word in sts:
    sol=sol*wdict[word]
    goodsol = goodsol*wdict_good[word]

if sol==1:
    for word in sts:
        print(trans[word][0],end=' ')
    print()
    if goodsol == 0:
        print("incorrect")
    else:
        print("correct")
else:
    print(goodsol,"correct")
    print(sol-goodsol,"incorrect")
        
