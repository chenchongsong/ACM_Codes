program shensou;
var a,b,c,pd:array[0..1003,0..1003]of longint;
    s:ansistring;
    i,j,k,max,n,m,p,t:longint;
function d(x,y:longint):boolean;
begin
  if (pd[x-1,y]=1) then exit(true);
  if (pd[x+1,y]=1) then exit(true);
  if (pd[x,y-1]=1) then exit(true);
  if (pd[x,y+1]=1) then exit(true);
  d:=false;
end;
function f(x,y:longint):longint;
begin
  f:=c[x-1,y];
  if pd[x+1,y]<>pd[x-1,y] then
    f:=f+c[x+1,y];
  if (pd[x,y-1]<>pd[x-1,y]) and (pd[x,y-1]<>pd[x+1,y]) then
    f:=f+c[x,y-1];
  if (pd[x,y+1]<>pd[x-1,y]) and (pd[x,y+1]<>pd[x+1,y])
     and (pd[x,y+1]<>pd[x,y-1]) then
       f:=f+c[x,y+1];
end;
procedure main(x,y:longint);
begin
  if (x=0) or (y=0) or (x=n+1) or (y=m+1)
  then exit;
  inc(c[i,j]); //writeln('!!',x,' ',y,' ',c[i,j]);
  b[x,y]:=1;
  if (a[x-1,y]=0) and (b[x-1,y]=0) then main(x-1,y);
  if (a[x,y-1]=0) and (b[x,y-1]=0) then main(x,y-1);
  if (a[x+1,y]=0) and (b[x+1,y]=0) then main(x+1,y);
  if (a[x,y+1]=0) and (b[x,y+1]=0) then main(x,y+1);
end;
procedure shua(x,y:longint);
begin
  if (x=0) or (y=0) or (x=n+1) or (y=m+1)
    then exit;
  c[x,y]:=c[i,j]; //writeln('??',x,' ',y,' ',c[i,j]);
  pd[x,y]:=p;
  if (a[x-1,y]=0) and (c[x-1,y]=0) then shua(x-1,y);
  if (a[x,y-1]=0) and (c[x,y-1]=0) then shua(x,y-1);
  if (a[x+1,y]=0) and (c[x+1,y]=0) then shua(x+1,y);
  if (a[x,y+1]=0) and (c[x,y+1]=0) then shua(x,y+1);
end;

begin
  readln(n,m,k);
  for i:=1 to n do
  begin
    readln(s);
    for j:=1 to m do
      a[i,j]:=ord(s[j])-ord('0');
  end;
  for i:=1 to n do
    for j:=1 to m do
      if (a[i,j]=0) and (c[i,j]=0) then
      begin
        inc(p);pd[i,j]:=p;
        main(i,j);
        shua(i,j);
      end;
  max:=0;
  if k=0 then
  begin
    for i:=1 to n do
      for j:=1 to m do
        if  c[i,j]>max then
          max:=c[i,j];
    writeln(max);
    halt;
  end;
  { for i:=1 to n do
  begin
    for j:=1 to m do write(c[i,j],' ');
    writeln;
  end; }

  for i:=1 to n do
    for j:=1 to m do
      if d(i,j) then
      begin
        t:=f(i,j);
        if t>max then max:=t;
      end;
  writeln(max+1);
end.




