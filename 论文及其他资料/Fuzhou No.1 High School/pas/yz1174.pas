program p1174;
var n,i,j:longint;
    a:array[1..1000000]of boolean;
begin
  readln(n);
  write('2');
  fillchar(a,sizeof(a),true);
  for i:=2 to trunc(sqrt(n)) do
    for j:=2 to (n div i) do
      a[i*j]:=false;
  for i:=3 to n do
    if a[i] then write(' ',i);
  writeln;
end.