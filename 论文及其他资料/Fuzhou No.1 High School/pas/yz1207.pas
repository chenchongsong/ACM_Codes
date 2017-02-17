program p1207;
const dx:array[1..4]of longint=(0,0,1,-1);
      dy:array[1..4]of longint=(1,-1,0,0);
var i,j,n,m,t,h,r,xx,yy,sx,sy,fx,fy,x,y:longint;
    dist:array[0..1001,0..1001]of longint;
    b:array[0..1001,0..1001]of boolean;
    qx,qy,f:array[0..1000003]of longint;
procedure init;
begin
  readln(n,m,t);
  readln(sx,sy,fx,fy);
  for i:=1 to t do
  begin
    readln(x,y);
    b[x,y]:=true;
  end;
end;
procedure bfs;
begin
  dist[sx,sy]:=1;
  h:=0;
  r:=1;
  qx[r]:=sx;
  qy[r]:=sy;
  while h<r do
  begin
    inc(h);
    x:=qx[h];
    y:=qy[h];
    for i:=1 to 4 do
    begin
      xx:=x+dx[i];
      yy:=y+dy[i];
      if (xx>=1) and (xx<=n) and (yy>=1) and (yy<=m)
        and (dist[xx,yy]=0) and (b[xx,yy]=false) then
        begin
          dist[xx,yy]:=dist[x,y]+1;
          inc(r);
          qx[r]:=xx;
          qy[r]:=yy;
          f[r]:=h;
        end;
      if (xx=fx) and (yy=fy) then
        break;
    end;
  end;
end;
procedure print(front:longint);
begin
  if front=0 then exit;
  print(f[front]);
  writeln(qx[front],' ',qy[front]);
end;
begin
  init;
  bfs;
  if dist[fx,fy]=0 then
  begin
    writeln('-1');
    halt;
  end;
  writeln(dist[fx,fy]);
  print(r);
end.
