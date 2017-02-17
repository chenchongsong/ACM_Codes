program p1850;
var i,j,k,n,m:longint;
    f:array[-1..1003,-1..1003]of int64;
begin
  readln(n,m);
  f[1,1]:=1;
  for i:=2 to n do
    for j:=1 to m do
      f[i,j]:=(f[i-1,j-2]+f[i-2,j-1]+f[i-1,j+2]+f[i-2,j+1]) mod 1000000007;
  writeln(f[n,m]);
end.
