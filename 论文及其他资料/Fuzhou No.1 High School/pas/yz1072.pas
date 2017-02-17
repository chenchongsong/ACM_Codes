program p1072;
var i,j,n,ans:longint;
    a,f:array[1..10001]of longint;
procedure find;
var i:longint;
begin
  for i:=3 to n do
    f[i]:=a[i-1]-f[i-2]-f[i-1];
  if f[n-1]+f[n]=a[n] then inc(ans);
end;
begin
  readln(n);
  for i:=1 to n do
    read(a[i]);
  if a[1]=3 then begin
    writeln('0');halt;
  end;
  ans:=0;
  fillchar(f,sizeof(f),0);
  if a[1]=2 then begin
    f[1]:=1;f[2]:=1;
    find;
  end;
  if a[1]=1 then begin
    f[1]:=1;f[2]:=0;
    find;
    fillchar(f,sizeof(f),0);
    f[1]:=0;f[2]:=1;
    find;
  end;
  if a[1]=0 then find;
  writeln(ans);
end.


