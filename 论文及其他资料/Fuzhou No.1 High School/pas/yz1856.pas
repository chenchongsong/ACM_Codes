program p1856;
var i,j,k,l,o,n,m,x:longint;
    a:array[-2..1000]of longint;
    b:array[1..4]of longint;
    f:array[-1..42,-1..42,-1..42,-1..42]of longint;
function max:longint;
begin
  max:=0;
  if f[i-1,j,k,l]>max then
    max:=f[i-1,j,k,l];
  if f[i,j-1,k,l]>max then
    max:=f[i,j-1,k,l];
  if f[i,j,k-1,l]>max then
    max:=f[i,j,k-1,l];
  if f[i,j,k,l-1]>max then
    max:=f[i,j,k,l-1];
end;
begin
  readln(n,m);
  for i:=1 to n do
    read(a[i]);
  for i:=1 to m do
  begin
    read(x);
    inc(b[x]);
  end;
  for i:=0 to b[1] do
    for j:=0 to b[2] do
      for k:=0 to b[3] do
        for l:=0 to b[4] do
          f[i,j,k,l]:=max+a[i+j*2+k*3+l*4+1];
  writeln(f[b[1],b[2],b[3],b[4]]);
end.
