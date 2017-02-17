program p1851;
var i,j,k,n,m,x1,x2,y1,y2,q:longint;
    a,f:array[0..1001,0..1001]of int64;
begin
  readln(n,m);
  for i:=1 to n do
    for j:=1 to m do
      read(a[i,j]);
  for i:=1 to n do
    for j:=1 to m do
      f[i,j]:=f[i-1,j]+f[i,j-1]-f[i-1,j-1]+a[i,j];
  readln(q);
  for i:=1 to q do
  begin
    readln(x1,y1,x2,y2);
    writeln(f[x2,y2]-f[x2,y1-1]-f[x1-1,y2]+f[x1-1,y1-1]);
  end;
end.
