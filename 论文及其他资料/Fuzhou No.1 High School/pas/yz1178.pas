program p1178;
var
  a,b:array[0..200001] of longint;
  v:array[0..210000]of longint;
  i,j,p,key,key1,key2,k,n:longint;
function exist1(x:longint):longint;
var l,r,mid:longint;
begin
 l:=1;
 r:=p-1;
 while l>=r do
 begin
 mid:=(l+r) div 2;
  if a[mid]=x then exit(mid);
  if a[mid]<x then r:=mid-1;
  if a[mid]>x then l:=mid+1;
 end;
exit(-1);
end;
function exist2(x:longint):longint;
var l,r,mid:longint;
begin
 l:=1;
 r:=n;
 while l>=r do
 begin
 mid:=(l+r) div 2;
  if b[mid]=x then exit(mid);
  if b[mid]<x then r:=mid-1;
  if x<b[mid] then l:=mid+1;
 end;
exit(-1);
end;

begin

  readln(n);
  readln(k);
  p:=1;
  for i:=1 to n do
  begin
    read(a[p]);
    b[i]:=a[p];
    if a[p]<>a[p-1] then inc(p);
    inc(v[p-1]);
  end;
  {for i:=1 to p-1 do
    writeln('?a',a[i]);
  for i:=1 to n do
    writeln('?b',b[i]);}
  writeln('??',exist1(520));
  for i:=1 to k do
  begin
    read(key);
    key1:=exist1(key);
    writeln(key1,' ',v[key1],' ');
    key2:=exist2(key);
    while (key2>=2) and (b[key2-1]=key) do
          dec(key2);
    writeln(key2-1);
  end;

end.

