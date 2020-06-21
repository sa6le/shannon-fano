#include <iostream>
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

struct node {
   string sym;
   float pro;
   int arr[20];
   int top;
} p[20];

typedef struct node node;

void shannon(int l, int h, node p[])

{

   float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
   int i, d, k, j;
   if ((l + 1) == h || l == h || l > h) {
       if (l == h || l > h)
           return;
       p[h].arr[++(p[h].top)] = 0;
       p[l].arr[++(p[l].top)] = 1;
       return;
   }
   else {
       for (i = l; i <= h - 1; i++)
           pack1 = pack1 + p[i].pro;
       pack2 = pack2 + p[h].pro;
       diff1 = pack1 - pack2;
       if (diff1 < 0)
           diff1 = diff1 * -1;
       j = 2;
       while (j != h - l + 1) {
           k = h - j;
           pack1 = pack2 = 0;
           for (i = l; i <= k; i++)
               pack1 = pack1 + p[i].pro;
           for (i = h; i > k; i--)
               pack2 = pack2 + p[i].pro;
           diff2 = pack1 - pack2;
           if (diff2 < 0)
               diff2 = diff2 * -1;
           if (diff2 >= diff1)
               break;
           diff1 = diff2;
           j++;
       }
       k++;
       for (i = l; i <= k; i++)
           p[i].arr[++(p[i].top)] = 1;
       for (i = k + 1; i <= h; i++)
           p[i].arr[++(p[i].top)] = 0;
       shannon(l, k, p);
       shannon(k + 1, h, p);
   }

}
void sortByProbability(int n, node p[])
{
   int i, j;
   node temp;
   for (j = 1; j <= n - 1; j++) {

       for (i = 0; i < n - 1; i++) {

           if ((p[i].pro) > (p[i + 1].pro)) {
               temp.pro = p[i].pro;
               temp.sym = p[i].sym;
               p[i].pro = p[i + 1].pro;
               p[i].sym = p[i + 1].sym;
               p[i + 1].pro = temp.pro;
               p[i + 1].sym = temp.sym;
           }
       }
   }
}
void display(int n, node p[])
{
   int i, j;
   cout << "Probability\tCode";
   for (i = n - 1; i >= 0; i--) {
       cout << "\n" <<  p[i].pro << "\t\t";
       for (j = 0; j <= p[i].top; j++)
           cout << p[i].arr[j];
   }
}

int main()

{
   system("title Shannon-Fano");
   int n, i, j;
   float total = 0;
   string ch;
   node temp;
//   cout << "Number of symbols:";
   n = 10;

//   double x[] = {0.062, 0.063, 0.065, 0.067, 0.07, 0.074, 0.079, 0.085, 0.093, 0.102, 0.113, 0.127};
//   double x[] = {0.0781, 0.0938, 0.125, 0.1563, 0.0313, 0.0313, 0.0313, 0.0469, 0.0938, 0.0313, 0.1563, 0.125};
//   double x[] ={0.017, 0.036, 0.054, 0.073, 0.091, 0.109, 0.128, 0.146, 0.164, 0.183};
   double x[] = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
   for (i = 0; i < n; i++) {
       p[i].pro = x[i];
       total = total + p[i].pro;
       if (total > 1.01) {
           cout << "Invalid. Enter new values" << endl;
           total = total - p[i].pro;
           i--;
       }

   }
   p[i].pro = 1 - total;
   sortByProbability(n, p);
   for (i = 0; i < n; i++)
       p[i].top = -1;
   shannon(0, n - 1, p);
   display(n, p);
   return 0;
}
