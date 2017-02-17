program p1082;
var i,j,k,n,sum,p:longint;
    x,y:array[1..100001]of longint;
function pd1(i,j,k:longint):boolean;
begin
  if ((x[i]=x[j])or(x[i]=x[k])or(x[j]=x[k]))
   and ((y[i]=y[j])or(y[i]=y[k])or(y[j]=y[k]))
  then pd1:=true
  else
    pd1:=false;
end;
function pd2(i,j,k:longint):boolean;
var a,b,c,t:longint;
begin
  a:=abs(x[i]-x[j])*abs(x[i]-x[j])
     +abs(y[i]-y[j])*abs(y[i]-y[j]);
  b:=abs(x[i]-x[k])*abs(x[i]-x[k])
     +abs(y[i]-y[k])*abs(y[i]-y[k]);
  c:=abs(x[j]-x[k])*abs(x[j]-x[k])
     +abs(y[j]-y[k])*abs(y[j]-y[k]);

  if a>b then begin
    t:=a;a:=b;b:=t;end;
  if b>c then begin
    t:=b;b:=c;c:=t;end;
  if a+b=c then exit(true);
  exit(false);
end;
begin
  readln(n);
  sum:=0;
  for i:=1 to n do
    readln(x[i],y[i]);
  for i:=1 to n do
    for j:=i+1 to n do
      for k:=j+1 to n do
        if (pd1(i,j,k)) and (pd2(i,j,k)) then
          inc(sum);
  writeln(sum);
end.
