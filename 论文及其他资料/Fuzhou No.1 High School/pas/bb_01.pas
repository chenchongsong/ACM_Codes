program p1028;
var m,n,i,j:longint;
    w,v:array[0..10003]of longint;
    f:array[-100..10003]of longint;
begin
  readln(m,n);
  for i:=1 to n do
    readln(w[i],v[i]);
  //for i:=1 to 10000 do
    //f[i]:=-99999;
  for i:=1 to n do
    for j:=m downto w[i] do
      if f[j-w[i]]+v[i]>f[j]
        then
          f[j]:=f[j-w[i]]+v[i];
  writeln(f[m]);
end.
