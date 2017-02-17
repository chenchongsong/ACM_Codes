program shensou;
var a,b,c:array[0..1003,0..1003]of longint;
    s:ansistring;
    i,j,k,kmin,sum,p,x1,y1,n,m,t,sx,sy,fx,fy:longint;
procedure main(x,y:longint);
begin
  if (x=0) or (y=0) or (x=n+1) or (y=n+1)
  then exit;
  inc(c[i,j]);
  b[x,y]:=1;
  if (a[x-1,y]<>a[x,y]) and (b[x-1,y]=0) then main(x-1,y);
  if (a[x,y-1]<>a[x,y]) and (b[x,y-1]=0) then main(x,y-1);
  if (a[x+1,y]<>a[x,y]) and (b[x+1,y]=0) then main(x+1,y);
  if (a[x,y+1]<>a[x,y]) and (b[x,y+1]=0) then main(x,y+1);
end;
procedure shua(x,y:longint);
begin
  if (x=0) or (y=0) or (x=n+1) or (y=n+1)
    then exit;
  c[x,y]:=c[i,j];
  if (a[x-1,y]<>a[x,y]) and (c[x-1,y]=0) then shua(x-1,y);
  if (a[x,y-1]<>a[x,y]) and (c[x,y-1]=0) then shua(x,y-1);
  if (a[x+1,y]<>a[x,y]) and (c[x+1,y]=0) then shua(x+1,y);
  if (a[x,y+1]<>a[x,y]) and (c[x,y+1]=0) then shua(x,y+1);
end;

begin
  readln(n,m);
  for i:=1 to n do
  begin
    readln(s);
    for j:=1 to n do
      a[i,j]:=ord(s[j])-ord('0');
  end;
  for i:=1 to n do
    for j:=1 to n do
      if c[i,j]=0 then
      begin
        main(i,j);
        shua(i,j);
      end;
  for i:=1 to m do
  begin
     readln(x1,y1);
     writeln(c[x1,y1]);
  end;
end.




