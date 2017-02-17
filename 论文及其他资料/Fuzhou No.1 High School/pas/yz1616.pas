program p1616;
var i,j,ans,key1,key2,n,c:longint;
    a,b:array[1..200001]of longint;
procedure qs(l,r:longint);
var tl,tr,mid,temp:longint;
begin
  tl:=l;tr:=r;
  mid:=a[(l+r)shr 1];
  repeat
    while a[tr]>mid do dec(tr);
    while a[tl]<mid do inc(tl);
    if tl<=tr then
    begin
      temp:=a[tl];a[tl]:=a[tr];a[tr]:=temp;
      inc(tl);dec(tr);
    end;
  until tl>tr;
  if tl<r then qs(tl,r);
  if tr>l then qs(l,tr);
end;
function exist(x:longint):longint;
var l,r,mid:longint;
begin
 l:=1;
 r:=n;
 while l<=r do
 begin
 mid:=(l+r) div 2;
  if a[mid]=x then exit(mid);
  if a[mid]<x then l:=mid+1;
  if x<a[mid] then r:=mid-1;
 end;
exit(-1);
end;
begin
  readln(n,c);
  for i:=1 to n do
    read(a[i]);
  qs(1,n);
  for i:=1 to n do
    b[i]:=a[i]+c;
  for i:=1 to n do
  begin
    key1:=exist(b[i]);
    key2:=key1;
    if key1<>-1
      then begin
        while (key1-1>=1) and (a[key1-1]=b[i]) do
          dec(key1);
        while (key2+1<=n) and (a[key2+1]=b[i]) do
          inc(key2);
        ans:=ans+key2-key1+1;
      end;
  end;
  writeln(ans);
end.




