program backpack_01;
var i,j,n,v:longint;
    f,c,w:array[-19999..1000]of longint;
function max(a,b:longint):longint;
begin
  if a>b then max:=a
  else
    max:=b;
end;
begin
 readln(v,n);
 for i:=1 to n do
   readln(w[i],c[i]);
 //for i:=1 to n do
   //f[i]:=-999999999;
 for i:=1 to n do
   for j:=c[i] to v do
     f[j]:=max(f[j],f[j-c[i]]+w[i]);
 writeln(f[11]);
end.
