program p1082;
var i,j,k,n,sum,x1,y1:longint;
    ans:int64;
    a:array[0..100001,1..2]of longint;
    xp,yp:array[0..100001]of int64;
begin
  readln(n);
  for i:=1 to n do
  begin
    readln(a[i,1],a[i,2]);
    inc(xp[a[i,1]]);
    inc(yp[a[i,2]]);
  end;
  for i:=1 to n do
    ans:=ans+(xp[a[i,1]]-1)*(yp[a[i,2]]-1);
  writeln(ans);
end.
