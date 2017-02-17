program p1043;
var i,j,k,len1,len2:longint;
    f:array[0..5001,0..5001]of longint;
    s1,s2:ansistring;
function max(x,y,z:longint):longint;
begin
  if (x>y) then
  begin
    if (x>z) then exit(x);
    exit(z);
  end;
  if (y>z) then exit(y);
  exit(z);
end;
function f1:longint;
begin
  if s1[i]=s2[j] then
    f1:=f[i-1,j-1]+1
  else
    f1:=f[i-1,j-1];
end;
function f2:longint;
begin
  f2:=f[i-1,j]-2;
end;
function f3:longint;
begin
  f3:=f[i,j-1]-2;
end;
begin
  readln(s1);
  readln(s2);
  len1:=length(s1);
  len2:=length(s2);
  if (s1=' ') or (s2=' ')
  then begin
    writeln('-2');
    halt;
  end;
  for i:=1 to len1 do
    f[i,0]:=i*(-2);
  for i:=1 to len2 do
    f[0,i]:=i*(-2);
  for i:=1 to len1 do
    for j:=1 to len2 do
      f[i,j]:=max(f1,f2,f3);
  writeln(f[len1,len2]);
end.