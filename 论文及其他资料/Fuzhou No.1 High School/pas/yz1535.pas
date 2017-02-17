program p1535;
var i,j,n,ans:longint;
begin
  readln(n);
  ans:=1;
  for i:=n+2 to n*2 do
    ans:=ans*i;
  for i:=1 to n do
    ans:=ans div i;
  writeln(ans);
end.