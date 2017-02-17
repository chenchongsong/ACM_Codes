program cs1;
var
  a:array[0..300000] of longint;
  y:int64;
  x,ans,head,c,tail,ii,i,j,n:longint;
  pt:boolean;

procedure qsort(l,r:longint);
var
  i,j,x,y:longint;
begin
  i:=l;
  j:=r;
  x:=a[(l+r) div 2];
  repeat
    while a[j]>x do
      dec(j);
    while a[i]<x do
      inc(i);
    if i<=j then
      begin
        y:=a[i];
        a[i]:=a[j];
        a[j]:=y;
        inc(i);
        dec(j);
      end;
  until i>j;
  if i<r then
    qsort(i,r);
  if j>l then
    qsort(l,j);
end;
procedure find(l,r:longint);
var
  tmp:longint;
begin
  tmp:=(l+r) div 2;
  if a[tmp]=y then
    begin
      pt:=true;
      ii:=tmp;
      exit;
    end;
  if l<>r then
    begin
      if (a[tmp]<y) and (r>=tmp+1) then
        find(tmp+1,r);
      if (a[tmp]>y) and (tmp-1>=l) then
        find(l,tmp-1);
    end;
end;
begin

  readln(n,c);
  for i:=1 to n do
    read(a[i]);
  qsort(1,n);
  for i:=1 to n do
    begin
      x:=a[i];
      y:=a[i]-c;
      pt:=false;
      find(1,n);
      if pt then
        begin
          if ii<>i then
            inc(ans);
          head:=ii-1;
          tail:=ii+1;
          while (a[head]=y) and (head>0) do
            begin
              inc(ans);
              dec(head);
            end;
          while (a[tail]=y) and (tail<=n) do
            begin
              inc(ans);
              inc(tail);
            end;
        end;
    end;
  writeln(ans);

end.
