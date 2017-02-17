program p1178;
var
  v,no1,no2:array[-1..10000]of longint;
  i,j,p,key,x,max,k,n:longint;
begin
  readln(n);
  readln(k);
  read(x);
  inc(v[x]);
  max:=x;
  for i:=2 to n do
  begin
    read(x);
    inc(v[x]);
  end;
  x:=-1;
  for i:=1000 downto 1 do
    if v[i]<>0 then
    begin
      inc(p);
      no1[i]:=p;
      no2[i]:=no2[x]+v[i];
      x:=i;
    end;
  for i:=1 to k do
  begin
    read(key);
    if v[key]=0 then begin
        writeln('Fail!');
        continue;
    end;
    writeln(no1[key],' ',v[key],' ',no2[key]-v[key]);
  end;

end.

