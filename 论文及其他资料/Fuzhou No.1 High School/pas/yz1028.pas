program p1028;
var m,n,i,j:longint;
    w,v:array[0..10003]of longint;
    f:array[0..10003]of int64;
begin
  readln(m,n);
  for i:=1 to n do
    readln(v[i],w[i]);
  for i:=1 to n do
    for j:=w[i] to m do
      if f[j-w[i]]+v[i]>f[j]
        then
          f[j]:=f[j-w[i]]+v[i];
  writeln(f[m]);
end.