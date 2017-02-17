program p1175;
var i,j,k,ans,n,t:longint;
    a,b:array[1..100]of longint;
function pd1(a1,b1,x,a2,b2:longint):boolean;
var temp:longint;
begin
  if (b1<=0) or (x<0)  then exit(false);
  if a1<b1 then begin
    temp:=a1;a1:=b1;b1:=temp;
  end;
  if (a1>=a2) and (b1>=b2) then exit(true);
  pd1:=false;
end;
function pd(ai,aj,ak,bi,bj,bk:longint):boolean;
var max:longint;
begin

  if ak>aj then begin
     t:=aj;aj:=ak;ak:=t;
     t:=bj;bj:=bk;bk:=t;
  end;
  if aj>ai then begin
     t:=ai;ai:=aj;aj:=t;
     t:=bi;bi:=bj;bj:=t;
  end;
  if (bi<bj) or (bi<bk)
    then exit(false);
  if pd1(ai,bi-bj,ai-aj,ak,bk) then exit(true);
  if pd1(bi,ai-aj,bi-bj,ak,bk) then exit(true);
  if pd1(ai,bi-aj,ai-bj,ak,bk) then exit(true);
  if pd1(bi,ai-bj,bi-aj,ak,bk) then exit(true);
  pd:=false;
end;
begin
  readln(n);
  for i:=1 to n do
  begin
    readln(a[i],b[i]);
    if a[i]<b[i] then begin
      t:=a[i];a[i]:=b[i];b[i]:=t;
    end;
  end;
  for i:=1 to n do
    for j:=i+1 to n do
      for k:=j+1 to n do
        if pd(a[i],a[j],a[k],b[i],b[j],b[k]) then inc(ans);
  writeln(ans);
end.
