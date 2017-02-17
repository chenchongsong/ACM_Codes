program p1028;
var m,n,i,j:longint;
    w,v:array[0..60003]of longint;
    f:array[0..60003]of int64;
begin
  readln(n);
  m:=trunc(sqrt(n));
  for i:=1 to m do
  begin
    w[i]:=i*i;
    v[i]:=1;
  end;
  for i:=1 to n do
    f[i]:=maxlongint;
  for i:=1 to m do
    for j:=w[i] to n do
      if f[j-w[i]]+v[i]<f[j]
        then
          f[j]:=f[j-w[i]]+v[i];
  writeln(f[n]);
end.
