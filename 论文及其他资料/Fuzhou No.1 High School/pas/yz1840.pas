program  p1840;
var i,j,n,m,ans:longint;
    f:array[0..100]of int64;
begin
  readln(n,m);
  ans:=1;
  for i:=0 to m-1 do
  begin
    f[i]:=1;
    for j:=1 to i do
      f[i]:=f[i]*2;
  end;
  f[m]:=f[m-1]*2-1;
  if n<=m then begin
    writeln(f[n]);halt;
  end;
  for i:=m+1 to n do
    f[i]:=f[i-1]*2-f[i-1-m];
  writeln(f[n]);
end.