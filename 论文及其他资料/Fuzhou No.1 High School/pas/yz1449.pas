program p1449;
var i,j,k,o,p,n,c,x,pl,pm,sum,vp:longint;
    t:string;
    l,m,a:array[-1..10010]of longint;
    v:array[1..1000]of string;
    //re:array[1..2000,1..10000]of int64;
    //za:array[-1..10010]of longint;
procedure main1;
var i:longint;
begin
  for i:=1 to n do
    if a[i]=1
      then a[i]:=0
    else
      a[i]:=1;
end;
procedure main2;
var i:longint;
begin
  for i:=1 to (n div 2+1) do
    if a[i*2-1]=0 then
      a[i*2-1]:=1
    else
      a[i*2-1]:=0;
end;
procedure main3;
var i:longint;
begin
  for i:=1 to (n div 2+1) do
    if a[i*2]=0 then
      a[i*2]:=1
    else
      a[i*2]:=0;
end;
procedure main4;
var i:longint;
begin
  for i:=0 to (n div 3+2) do
    if a[i*3+1]=0 then
      a[i*3+1]:=1
    else
      a[i*3+1]:=0;
end;
function pd:boolean;
var i:longint;
begin
  for i:=1 to pl-1 do
    if a[l[i]]=0 then exit(false);
  for i:=1 to pm-1 do
    if a[m[i]]=1 then exit(false);
  pd:=true;
end;
begin
  readln(n);
  readln(c);
  if c>4 then
    if c mod 2=0 then c:=4
     else c:=3;
  while x<>-1 do
  begin
    read(x);
    inc(pl);
    l[pl]:=x;
  end;
  x:=0;
  while x<>-1 do
  begin
    read(x);
    inc(pm);
    m[pm]:=x;
  end;
  for i:=0 to 1 do
    for j:=0 to 1 do
      for k:=0 to 1 do
        for o:=0 to 1 do
        begin
          for p:=1 to n do
            a[p]:=1;
          if i=1 then main1;
          if j=1 then main2;
          if k=1 then main3;
          if o=1 then main4;
          sum:=i+j+k+o;
          if (pd=true) and ((sum=c) or (sum+2=c) or (sum+4=c)) then
          begin
            inc(vp);
            v[vp]:='';
            for p:=1 to n do
              v[vp]:=v[vp]+chr(ord('0')+a[p]);
          end;
        end;
    for i:=1 to vp-1 do
      for j:=i+1 to vp do
        if v[i]>v[j] then
        begin
          t:=v[i];v[i]:=v[j];v[j]:=t;
        end;
      for i:=1 to vp do
      writeln(v[i]);
     {
        for p:=1 to n do
      //v[vp]:=v[vp]*2+a[p];
     for i:=1 to vp do
     begin
       t:=1;
       while v[i]<>0 do
       begin
         za[t]:=v[i] mod 2;
         v[i]:=v[i] div 2;
         inc(t);
       end;
       write(za[n]);
       for j:=n-1 downto 1 do
         write(' ',za[j]);
       writeln;
     end; }
end.











