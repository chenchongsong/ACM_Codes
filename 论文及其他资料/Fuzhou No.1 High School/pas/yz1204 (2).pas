program p1204;
const cc:array[1..3]of char=(' ','+','-');
var s:string;
    a:array[1..100]of char;
    z:array[1..10]of longint;
    c:array[1..10]of char;
    i,j,k,n:longint;
function pd(x:longint):longint;
var f,p:longint;
begin
  f:=1;
  p:=0;
  for i:=1 to n do
  begin
    if a[i]=' ' then
      f:=f*10+i+1;
    if a[i]='+' then
    begin
      inc(p);
      c[p]:='+';
      z[p]:=f;
      f:=i+1;
    end;
    if a[i]='-' then
    begin
      inc(p);
      c[p]:='-';
      z[p]:=f;
      f:=i+1;
    end;
  end;
  pd:=z[1];
  for i:=1 to p-1 do
    if c[i]='+' then
      pd:=pd+z[i+1]
    else
      pd:=pd-z[i+1];
end;
procedure print;
begin
  write('1');
  for i:=1 to n-1 do
  write(a[i],i+1);
  writeln;
end;
procedure main(x:longint);
begin
  if x=n then
  begin
    if pd(1)=0 then
      print;
    exit;
  end;
  a[x]:=' ';
  main(x+1);
  a[x]:='+';
  main(x+1);
  a[x]:='-';
  main(x+1);
end;
begin
  readln(n);
  a[n]:='+';
  main(1);
end.
