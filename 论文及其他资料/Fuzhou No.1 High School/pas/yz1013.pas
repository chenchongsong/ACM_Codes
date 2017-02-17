program p1013;
var i,j,k,n:longint;
    f:array[0..100,0..100]of int64;
begin
  readln(n,k);
  for i:=1 to 100 do
    f[i,1]:=1;
  for i:=2 to n do
    for j:=2 to k do
      f[i,j]:=f[i-1,j]*j+f[i-1,j-1]*(i-j+1);
  writeln(f[n,k]);
end.
