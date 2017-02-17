program p1178;
var
  v,no1,no2:array[-999..10000]of longint;
  i,j,p,key,x,k,n:longint;

begin
  readln(n);
  readln(k);
  for i:=1 to n do
  begin
    read(x);
    inc(v[x]);
  end;
  for i:=1000 downto 1 do
    if v[i]<>0 then
    begin
      inc(p);
      no1[i]:=p;
      no2[i]:=no2[i-1]+v[i];
    end;
  for i:=1 to k do
  begin
    read(key);
    if v[key]=0 then begin
        writeln('Fail!');
        continue;
    end;
    writeln(no1[i],' ',v[i],' ',no2[i]-v[i]);
  end;

end.

