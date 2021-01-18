uses GraphABC;
var p:picture;
    p2:picture;
    p3:picture;
    w,h:integer;
    w1, h1:integer;
    start, finish: real;
    cof:real;
    dif:real;
    p_c:color;
    cur_c: color;
    name:string;
begin
writeln('Введите название изображения: ');
read(name);
p:= Picture.Create(name);
w:= p.Width;
h:= p.Height;
writeln('Размер вашего изображения: ', w , ' * ', h);
writeln('Увеличить по ширине до: ');  read(w1);
writeln('Увеличить по высоте до: ');  read(h1);
p2:= Picture.Create(w1, h);
cof:= w1 / w;
writeln(cof);
for i:integer:= 0 to h-1 do
  for j:integer:= 0 to w-1 do
    begin
    start:= j * cof;
    finish:= start + cof;
    p_c:= p.Getpixel(j,i);
    {writeln('p_c: ' , p_c);
    writeln('start: ', start, '  finish: ', finish);}
    if(start <> int(start)) then
      begin
      cur_c:= p2.GetPixel(floor(j*cof), i);
      {writeln('Старый цвет пиксела ', floor(j*cof), ' ', i, ': ' ,cur_c);}
      dif:= 1 - (start - int(start));
      p2.SetPixel(floor(j*cof), i, RGB(floor(p_c.R*dif)+cur_c.R, floor(p_c.G*dif)+cur_c.G, floor(p_c.B*dif)+cur_c.B));
      //log.Writeln(round(p_c.R*dif)+cur_c.R, round(p_c.G*dif)+cur_c.G,round(p_c.B*dif)+cur_c.B);
      {writeln('Крашу(start) пиксель* ', floor(j*cof), ' ' ,i, ' цветом',RGB(round(p_c.R*dif)+cur_c.R, round(p_c.G*dif)+cur_c.G, round(p_c.B*dif)+cur_c.B) );}
      end;
    for a:integer:= ceil(start) to floor(finish)-1 do 
      begin
      p2.SetPixel(a,i, p_c);
      {writeln('Крашу (process) пиксель ',a, ' ' ,i,' цветом',RGB(round(p_c.R*dif), round(p_c.G*dif), round(p_c.B*dif)) );}
      end;
    if(finish <> int(finish)) then
      begin
      if(floor(finish)>= w1) then
      begin
      break;
      end;
      dif:= finish-int(finish);
      p2.SetPixel(floor(finish), i, RGB(floor(p_c.R*dif), floor(p_c.G*dif), floor(p_c.B*dif)));
            {writeln('Крашу (finish) пиксель ', floor(finish), ' ' ,i, ' цветом',RGB(round(p_c.R*dif), round(p_c.G*dif), round(p_c.B*dif)) );}
      end;
    
    end;
p2.Save('width.png');
writeln('Width done!');
/////////
p:= p2;
p2:= Picture.Create(w1, h1);

cof:= h1 / h;
writeln(cof);
for i:integer:= 0 to w1-1 do
  for j:integer:= 0 to h-1 do
    begin
    start:= j * cof;
    finish:= start + cof;
    p_c:= p.Getpixel(i,j);
    {writeln('p_c: ' , p_c);
    writeln('start: ', start, '  finish: ', finish);}
    if(start <> int(start)) then
      begin
      cur_c:= p2.GetPixel(i, floor(j*cof));
      {writeln('Старый цвет пиксела ', floor(j*cof), ' ', i, ': ' ,cur_c);}
      dif:= 1 - (start - int(start));
      p2.SetPixel(i, floor(j*cof), RGB(floor(p_c.R*dif)+cur_c.R, floor(p_c.G*dif)+cur_c.G, floor(p_c.B*dif)+cur_c.B));
      {writeln('Крашу(start) пиксель* ', floor(j*cof), ' ' ,i, ' цветом',RGB(round(p_c.R*dif)+cur_c.R, round(p_c.G*dif)+cur_c.G, round(p_c.B*dif)+cur_c.B) );}
      end;
    for a:integer:= ceil(start) to floor(finish)-1 do 
      begin
      p2.SetPixel(i,a, p_c);
     
      {writeln('Крашу (process) пиксель ',a, ' ' ,i,' цветом',RGB(round(p_c.R*dif), round(p_c.G*dif), round(p_c.B*dif)) );}
      end;
    if(finish <> int(finish)) then
      begin
      dif:= finish-int(finish);
      if(floor(finish)>= h1) then
      begin
      break;
      end;
      p2.SetPixel(i, floor(finish), RGB(floor(p_c.R*dif), floor(p_c.G*dif), floor(p_c.B*dif)));
            {writeln('Крашу (finish) пиксель ', floor(finish), ' ' ,i, ' цветом',RGB(round(p_c.R*dif), round(p_c.G*dif), round(p_c.B*dif)) );}
      end;  
    end;
p2.draw(0,0);
p2.Save('res.png');
writeln('done!');

end.