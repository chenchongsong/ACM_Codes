program p1786;
var i,j,k,n:longint;
    d_all,cost:int64;
    t,d,num:array[1..100009]of longint;
    a:array[1..1000000]of extended;
procedure qs(l,r: longint);
      var
         i,j,t:longint;
         x,y:extended;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]<x do
            inc(i);
           while x<a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                t:=num[i];
                num[i]:=num[j];
                num[j]:=t;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           qs(l,j);
         if i<r then
           qs(i,r);
      end;
begin
  readln(n);
  for i:=1 to n do
  begin
    readln(t[i],d[i]);
    a[i]:=t[i]/d[i];
    d_all:=d_all+d[i];
    num[i]:=i;
  end;
  qs(1,n);
  for i:=1 to n-1 do
  begin
    d_all:=d_all-d[num[i]];
    cost:=cost+d_all*t[num[i]];
  end;
  writeln(cost);
end.



