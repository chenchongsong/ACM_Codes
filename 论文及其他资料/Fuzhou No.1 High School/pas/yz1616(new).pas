program cs1;
var
  a:array[0..200001] of longint;
  v:array[0..210000000]of longint;
  i,j,ans,c,n:longint;
begin
  ans:=0;
  readln(n,c);
  for i:=1 to n do
  begin
    read(a[i]);
    inc(v[a[i]]);
  end;
  for i:=1 to n do
  begin
    if a[i]-c>=0 then
    ans:=ans+v[a[i]-c];
  end;
  writeln(ans);

end.
