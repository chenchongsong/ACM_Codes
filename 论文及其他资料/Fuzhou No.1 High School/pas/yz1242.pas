program fruit;
var i,j,n,c:longint;
    ans,x,y,len:int64;
    a:array[-1..30000]of longint;
procedure swap(var a,b:longint);
var temp:longint;
begin
  temp:=a;a:=b;b:=temp;
end;
procedure put(c:longint);
var son,temp:longint;
begin
  inc(len);
  a[len]:=c;
  son:=len;
  while (son<>1) and (a[son]<a[son div 2]) do
  begin
    swap(a[son],a[son div 2]);
    son:=son div 2;
  end;
end;
function get:longint;
var fa,son:longint;
begin
  get:=a[1];
  a[1]:=a[len];
  dec(len);
  fa:=1;
  while fa*2<=len do
  begin
    if (a[fa*2]<a[fa*2+1]) or(fa*2+1>len) then son:=fa*2
    else
      son:=fa*2+1;
    if a[fa]>a[son] then
      begin
        swap(a[fa],a[son]);
        fa:=son;
      end
    else
      break;
  end;
end;

begin
  readln(n);
  for i:=1 to n do
  begin
    read(c);
    put(c);
  end;
  for i:=1 to n-1 do
  begin
    x:=get;
    y:=get;
    ans:=ans+x+y;
    put(x+y);
  end;
  writeln(ans);
end.
