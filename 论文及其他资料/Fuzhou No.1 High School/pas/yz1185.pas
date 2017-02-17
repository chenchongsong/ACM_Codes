program p1185;
var b:array[1..10001000]of boolean;
    a:array[1..1000000]of longint;
    s:array[1..5001]of longint;
    n,i,j,k,p:longint;
    ss:string;
    ans:int64;
begin
  readln(n,k);
  for i:=1 to k do
    read(s[i]);
  for i:=1 to n do
  begin
    p:=i;
    str(i,ss);
    for j:=1 to length(ss) do
      p:=p+ord(ss[j])-ord('0');
    b[p]:=true;
  end;
  p:=0;
  for i:=1 to n do
  if b[i]=false then begin
    inc(p);
    a[p]:=i;
  end;
  writeln(p);
  for i:=1 to k do
    write(a[s[i]],' ');
  writeln;
end.