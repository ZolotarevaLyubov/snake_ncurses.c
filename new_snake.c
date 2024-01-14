#include <ncurses.h>
#include <stdlib.h>

int rand_y, rand_x;
int ymax, xmax;
int mult_yx;
int* arry;
int* arrx;
int limit_snake = 0;
int start_snake = 0;
bool game_over = false;
int clash_snake(int y, int x);
void rand_yx ()
{
  rand_y = rand() % ymax;
  rand_x = rand() % xmax;
  if (clash_snake (rand_y, rand_x) == 0)
  rand_yx();
  curs_set(0);//delete cursor
}


void print_arr ()
{
 if (start_snake < limit_snake) 
 {
 for(int i = start_snake; i < limit_snake; i++)
 {
   mvaddstr (arry[i], arrx[i], "o");   
 }
}
 
 else
{
 for (int j = 0; j < limit_snake; j++)
 {
   mvaddstr (arry[j], arrx[j], "o");
 }
 for (int s = start_snake; s < mult_yx; s++)
 {
   mvaddstr (arry[s], arrx[s], "o");
 }
}
}
//print snake

 


void new_limit (int new_y, int new_x)
{
  
  arry[limit_snake] = new_y;
  arrx[limit_snake] = new_x;
  limit_snake++;
  if (limit_snake == mult_yx)
  limit_snake = 0;
 
}
//increase snake


void delete_snake ()
{
 start_snake++;
 if (start_snake == mult_yx)
 start_snake = 0;
}

int clash_snake (int y, int x)
{
if (start_snake < limit_snake)
{
 for (int i = start_snake; i < limit_snake; i++)
 {
  if (arry[i] == y && arrx[i] == x)
  return 0;
 }
}
else
{ 
 for (int j = 0; j < limit_snake; j++)
 {
  if (arry[j] == y && arrx[j] == x)
  return 0;
 }
 for (int s = start_snake; s < mult_yx; s++)
 {
  if (arry[s] == y && arrx[s] == x)
  return 0;
 }
} 
 return 1;
}

void erase_snake()
{
 erase();
}

int main()
{
 initscr ();
 int x = 0;
 int y = 0;

 getmaxyx(stdscr, ymax, xmax);
 mult_yx = ymax * xmax;
 //mult_yx = 10;
 arry = malloc (sizeof(int) * mult_yx);
 arrx = malloc (sizeof(int) * mult_yx);
 rand_yx();
 new_limit(y, x);
 int dx, dy;
 halfdelay(1);
 for (; ; )
 {
  erase_snake ();
  print_arr();
  mvaddstr (rand_y, rand_x, "a");
  
  int a = getch ();
  if (a == 'a' || a == 'A')
    {
    dx = -1;
    dy = 0;
    }
  else if (a == 'w' || a == 'W')
    {
    dy = -1;
    dx = 0;
    }
  else if (a == 's' || a == 'S')
    {
    dy = 1;
    dx = 0;
    }
  else if (a == 'd' || a == 'D')
    {
    dx = 1;
    dy = 0;
    }
  x = x + dx;
  y = y + dy;
  if (x >= xmax)
    x = 0;
  else if (y >= ymax)
    y = 0;
  else if (x < 0)
    x = xmax - 1;
  else if (y < 0)
    y = ymax - 1;
    
  if (clash_snake (y, x) == 0)
    break;  
        
  new_limit(y, x);
   if (rand_y == y && rand_x == x)
    rand_yx();
   else 
    delete_snake();
     
 }
 
endwin ();
}

