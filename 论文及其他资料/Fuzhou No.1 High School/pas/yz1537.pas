program p1537;
var i,j,k,n,c:longint;
    m,w:array[1..1000]of longint;
    f:array[0..20003]of longint;
procedure complete(w:longint);
var j:longint;
begin
  for j:=w to c do
    if f[j-w]+1<f[j]
      then
        f[j]:=f[j-w]+1;
end;
procedure zeroone(w,v:longint);
var j:longint;
begin
  for j:=c downto w do
    if f[j-w]+1<f[j]
      then
        f[j]:=f[j-w]+v;
end;
begin
  readln(n);
  for i:=1 to n do
    read(w[i]);
  for i:=1 to n do
    read(m[i]);
  readln(c);
  for i:=1 to n do
    f[i]:=maxlongint-1;
  for i:=1 to n do
  begin
    if w[i]*m[i]>=c
    then begin
      complete(w[i]);
      continue;
    end;
    k:=1;
    while k<m[i] do
    begin
      zeroone(k*w[i],k);
      m[i]:=m[i]-k;
      k:=k*2;
    end;
    zeroone(w[i]*m[i],m[i]);
  end;
  writeln(f[n]);
end.







