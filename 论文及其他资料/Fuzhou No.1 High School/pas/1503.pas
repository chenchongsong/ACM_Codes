program p1503;
var i,j,k,n:longint;
    f:array[-3..80] of int64;
begin
  readln(n);
  f[0]:=1;
  f[1]:=1;
  f[2]:=1;
  for i:=3 to n do
    f[i]:=f[i-1]+f[i-3];
  writeln(f[n]);
end.