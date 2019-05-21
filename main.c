#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

typedef struct _point
{
  int *x;
} POINT;

typedef struct _list
{
  int d;
  struct _list *next;
} LIST;

int dis(POINT *p)
{
  int dis = 0;
  for (int i = 0; i < 100; i++)
  {
    dis = dis + (p->x[i] * p->x[i]);
  }
  dis = sqrt(dis);
  return dis;
}

void swap(POINT *x, POINT *y)
{
  int *temp;

  temp = x->x;
  x->x = y->x;
  y->x = temp;
}

void insert_heap(POINT *p, POINT **array)
{

  int len = 0;
  int child, parent, d1, d2;

  while (array[len] != NULL)
  {
    len++;
  }
  array[len] = p;

  child = len;
  parent = len / 2;
  while (parent >= 1)
  {
    d1 = dis(array[child]);
    d2 = dis(array[parent]);
    if (d1 > d2)
    {
      swap(array[child], array[parent]);
    }
    child = parent;
    parent = child / 2;
  }
}

bool check_heep(POINT **heep, int n)
{
  int i = 1;
  while ((2 * i + 1) < n)
  {
    if (heep[i] > heep[i * 2])
    {
      return false;
    }
    if (heep[i] > heep[i * 2 + 1])
    {
      return false;
    }
    i++;
  }
  return true;
}

int main(int argc, char const *argv[])
{
  /*100次元の点をn個作成*/
  int r, M = 100;        //Mはrandの最大
  int n = atoi(argv[1]); //nは作る点の数
  //int n = 1000;
  POINT **p;
  p = (POINT **)malloc(sizeof(POINT *) * n);

  for (int i = 0; i < n; i++)
  {
    p[i] = (POINT *)malloc(sizeof(POINT));
    p[i]->x = (int *)malloc(sizeof(int) * 100);
  }

  for (int j = 0; j < n; j++)
  {
    for (int i = 0; i < 100; i++)
    {
      r = (int)rand() % M;
      p[j]->x[i] = r;
    }
  }
  /*ここまで*/

  POINT **heap;
  double time;
  clock_t start, end;

  heap = (POINT **)malloc(sizeof(POINT *) * (n + 1));

  for (int i = 1; i < (n + 1); i++)
  {
    heap[i] = NULL;
  }
  heap[0] = (POINT *)malloc(sizeof(POINT));
  heap[0]->x = 0;

  start = clock();

  for (int i = 0; i < n; i++)
  {
    insert_heap(p[i], heap);
  }

  end = clock();
  time = (double)(end - start) / CLOCKS_PER_SEC;

  // for (int i = 1; i < n + 1; i++)
  // {
  //   printf("%d,", dis(heap[i]));
  // }
  // printf("\n");

  // printf("%d\n", check_heep(heap, n));

  printf("%f", time);
  return 0;
}
