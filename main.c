#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

typedef struct _point
{
  int *x;
} POINT;

typedef struct _node
{
  int data;
  struct _node *left;
  struct _node *right;
} NODE;

typedef struct _list
{
  int d;
  struct _list *next;
} LIST;

NODE *init_node()
{
  NODE *p;
  p = (NODE *)malloc(sizeof(NODE));
  p->data = 0;
  p->left = NULL;
  p->right = NULL;
  return p;
}

int dis(POINT *p)
{
  int dis = 0;
  for (int i = 0; i < 100; i++)
  {
    dis = dis + (p->x[i] * p->x[i]);
  }
  //dis = sqrt(dis);
  return dis;
}

/* 値を入れ替える関数 */
void swap(POINT *x, POINT *y)
{
  int *temp; // 値を一時保存する変数

  temp = x->x;
  x->x = y->x;
  y->x = temp;
}

/* pushdouwn操作 */
void pushdown(POINT **array, int first, int last)
{
  int parent = first;     // 親
  int child = 2 * parent; // 左の子
  while (child <= last)
  {
    if ((child < last) && (dis(array[child]) < dis(array[child + 1])))
    {
      child++; // 右の子の方が大きいとき、右の子を比較対象に設定
    }
    if (dis(array[child]) <= dis(array[parent]))
    {
      break;
    } // ヒープ済み
    swap(array[child], array[parent]);
    parent = child;
    child = 2 * parent;
  }
}

/* ヒープソート */
void heap_sort(POINT **array, int array_size)
{
  int i;

  for (i = array_size / 2; i >= 1; i--)
  {
    pushdown(array, i, array_size); // 全体をヒープ化
  }
  for (i = array_size; i >= 2; i--)
  {
    swap(array[1], array[i]);  // 最大のものを最後に
    pushdown(array, 1, i - 1); // ヒープ再構築
  }
}

void insert_heap(POINT *p, POINT **array)
{

  int len = 0;

  while (array[len] != NULL)
  {
    len++;
  }

  array[len] = p;

  //int data = dis(array[len]);

  //array[len] = data;

  heap_sort(array, len);
}

int main(int argc, char const *argv[])
{
  /*100次元の点をn個作成*/
  int r, M = 100; //Mはrandの最大
  //int n = atoi(argv[1]); //nは作る点の数
  int n = 1000;
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
    printf("%d\n", i);
  }

  end = clock();
  time = (double)(end - start) / CLOCKS_PER_SEC;
  //printf("%f", time);

  for (int i = 1; i < n + 1; i++)
  {
    printf("%d,", dis(heap[i]));
  }
  printf("\n");

  printf("%f\n", time);
  return 0;
}
