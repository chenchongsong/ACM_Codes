program p1314;
var i,j,k,n,a,b,min,max:longint;
    f,ex:array[-1..1000000]of longint;
begin
  readln(n);
  min:=maxlongint;
  for i:=1 to n do
  begin
    readln(a,b);
    if a>ex[b] then ex[b]:=a;
    if b<min then min:=b;
    if b>max then max:=b;
  end;
  for i:=min to max do
    if f[ex[i]]+1>f[i-1] then
      f[i]:=f[ex[i]]+1
    else
      f[i]:=f[i-1];
  writeln(f[max]);
end.
