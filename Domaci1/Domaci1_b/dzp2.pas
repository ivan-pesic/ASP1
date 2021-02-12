program dzp2;
uses crt ;

type

elements = record
data: real;
flag : integer;
end;

type_arr = array[65..90] of elements;

TPNode = ^TNode;
TNode = record
data : real ;
next : TPNode ;
end;

var
menu_choice, flag, expr_flag : integer ;
expr : string ;
arr : type_arr ;

function menu() : integer ;
         var
           choice : integer ;
  begin
       writeln();
       writeln('MENI') ;
       writeln();
       writeln('1. Unos i provera korektnosti aritmetickog izraza');
       writeln('2. Unos vrednosti simbolickih operanada');
       writeln('3. Izracunavanje aritmetickog izraza');
       writeln('4. Promena vrednosti simbolickom operandu');
       writeln('5. Kraj rada');
       writeln();
       write('Izabrati zeljeni podmeni: ');
       readln( choice ) ;
               while ( ( choice < 1 ) or ( choice > 5 ) ) do
               begin
               write( 'Nekorektan unos. Unesite zeljeni podmeni ponovo: ' );
               readln(choice) ;
               end;



       menu := choice ;
  end;

function upp( c : char ) : boolean ;
begin
     upp := (c>='A') and (c<='Z') ;
end;

function op( c : char ) : boolean ;
begin
     op := (c='+') or (c='-') or (c='/') or (c='*') ;
end;

procedure menu_1(var expr : string ; var flag : integer);
var

    len, i, st_ptr : integer ;
    syntax : boolean ;

begin
    clrscr;
    writeln('Podmeni 1. Unos i provera korektnosti aritmetickog izraza.');
    writeln();
    writeln('Uneti aritmeticki izraz: ');
    readln(expr);

    len := length(expr) ;
    i := 1;
    st_ptr := 1;
    syntax := true ;

    while (i <= len) and (st_ptr > 0) and syntax do begin
        inc(i);

        if(upp(expr[i])) then
          inc(st_ptr)

        else if (op(expr[i])) then
          dec(st_ptr)

        else syntax := false ;
    end;

    if st_ptr = 1 then
      begin
      writeln('Uneti izraz je korektan.') ;
      flag := 1 ;
      end

    else
      begin
      writeln();
      writeln('Uneti izraz nije korektan. Uneti izraz ponovo u podmeniju 1.');
      flag := 0 ;
      end;

end;

procedure initialize(var arr : type_arr);
var
    i : integer ;
begin
    for i := 65 to 90 do
        arr[i].flag := 0;
end;

procedure menu_2(var arr : type_arr; expr : string);
var
    len, i, id : integer ;
begin
     len := length(expr) ;
     clrscr;
     writeln('Podmeni 2. Unos operanada');
     for i:=1 to len do begin
         if( upp(expr[i])) then begin
             id := ord(expr[i]);
             if arr[id].flag = 0 then begin
                 write('Uneti vrednost parametra ',expr[i],': ');
                 readln(arr[id].data);
                 arr[id].flag := 1;
             end;
         end;
     end;

end;

function calculate(a, b : real; op : char; var flag : integer): real ;
begin
    if op='+' then
      calculate := a+b

    else if op='-' then
      calculate := a-b

    else if op='*' then
      calculate := a*b

    else
      begin
          if b<>0 then
            calculate := a/b
          else
                 flag := 1;

      end;

end;

procedure push(var stack : TPNode; val : real);
var node : TPNode;
begin
    new(node);
     if(stack^.next = stack) then
       begin
       node^.data := val;
       stack^.next:=node;
       node^.next := stack;
       end
     else
       begin
       node^.data := val;
       node^.next := stack^.next;
       stack^.next := node ;
       end;
end;


function pop(var stack : TPNode) : real ;
var
    node : TPNode;
begin
     node := stack^.next;
     stack^.next := node^.next;
     pop := node^.data;
     dispose(node);

end;

procedure deleteStack(var stack : TPNode) ;
var
    node : TPNode;

begin
    while(stack^.next <> stack) do
    begin
     node := stack^.next;
     stack^.next := node^.next;
     dispose(node);
    end;
end;

procedure menu_3(arr : type_arr ; expr : string) ;
var
    len, i, id, flag : integer;
    res, oprnd1, oprnd2 : real;
    stack: TPNode;
begin
    len := length(expr) ;
    flag := 0;
    new(stack);
    stack^.next := stack;
    clrscr;
    for i := 1 to len do begin
        if(upp(expr[i])) then
          begin
          id := ord(expr[i]);
          push(stack, arr[id].data);
          end
        else
          begin
               oprnd2 := pop(stack);
               oprnd1 := pop(stack);

               res := calculate(oprnd1, oprnd2, expr[i], flag);
               if(flag = 1) then
                 begin
                 writeln('Greska. Deljenje nulom nije dozvoljeno.');
                 deleteStack(stack);
                 break;
                 end

               else
                 push(stack, res);
          end;
    end;

    if(flag = 0) then
    begin
      res := pop(stack);
      writeln('Rezultat izraza je: ', res:2:2);
    end;
     dispose(stack);

end;

procedure menu_4(var arr : type_arr);
var val : real ;
    op : char ;
begin
    clrscr;
    writeln('Podmeni 4. Menjanje vrednosti odredjenom operandu.');
    writeln();
    write('Uneti operand i njegovu vrednost: ');
    readln(op, val);
    if (op >= 'A') and (op <= 'Z') then
       if arr[ord(op)].flag = 1 then
          arr[ord(op)].data := val
       else
          writeln('Greska. Uneti operand se ne nalazi u izrazu.')
    else
          writeln('Greska. Nekorektan unos.');
end;

begin
      writeln('Zadatak 2. Evaluacija aritmetickog izraza koriscenjem steka.');

     menu_choice := menu() ;
     flag := 0 ;
     expr_flag := 0 ;
     while ( menu_choice <> 5 ) do begin

       if menu_choice = 1 then begin
           menu_1(expr, flag);
       end

       else if menu_choice = 2 then begin
          if (flag=1) then
            begin
            initialize(arr) ;
            menu_2(arr, expr) ;
            expr_flag := 1;
            end

          else
            writeln('Greska. Izraz nije unet.');
       end

       else if menu_choice = 3 then begin
          if (flag=1) and (expr_flag = 1) then
            menu_3(arr, expr)
          else
            begin
                 if(flag = 0) then
                 writeln('Greska. Izraz nije unet.');
                 if(expr_flag = 0) then
                 writeln('Greska. Nisu unete vrednosti operanada.');
            end;

       end

       else if menu_choice = 4 then begin
           if (flag=1) and (expr_flag = 1) then
            menu_4(arr)
          else
            begin
                 if(flag = 0) then
                 writeln('Greska. Izraz nije unet.');
                 if(expr_flag = 0) then
                 writeln('Greska. Nisu unete vrednosti operanada.');
            end;
       end;

     writeln();
     menu_choice:=menu();

     end;
end.
