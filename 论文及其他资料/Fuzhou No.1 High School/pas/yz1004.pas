program p1004;
var i,j,k,n,a,b,c,d:longint;
    f:array[1..10001,1..4]of int64;
begin
  readln(n);
  f[1,1]:=1;
  for i:=2 to n do
  begin
    f[i,1]:=f[i-1,3] mod 7654321;
    f[i,2]:=f[i-1,4] mod 7654321;
    f[i,3]:=(f[i-1,1]+f[i-1,4]) mod 7654321;
    f[i,4]:=(f[i-1,2]+f[i-1,3]) mod 7654321;
  end;
  writeln((f[n,1]+f[n,2]+f[n,3]+f[n,4]) mod 7654321);
end.
