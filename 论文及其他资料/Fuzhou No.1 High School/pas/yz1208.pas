program yz1028;
var m,n,i,j:longint;
    s,t:array[1..10002]of longint;
    f:array[0..10002,0..10002]of longint;
begin
  readln(m,n);
  for i:=1 to n do
    readln(s[i],t[i]);
  for i:=1 to n do
    for j:=1 to m do
      if (j>=t[i]) and (f[i,j-t[i]]+s[i]>f[i-1,j]) then
        f[i,j]:=f[i,j-t[i]]+s[i]
      else
        f[i,j]:=f[i-1,j];

  writeln(f[n,m]);
end.
