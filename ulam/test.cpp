#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <utility>

using namespace std;

#ifdef _MSC_VER
#define and &&
#define not !
#endif

const int inches = 8;

// Target DPI: 300
const int DPI = 600;
const int dotw = 6;
const int doth = 6;

const int W = inches*DPI;
const int H = inches*DPI;

const int DOTW = W/dotw - 1;
const int DOTH = H/doth - 1;

const int dots = DOTW*DOTH;

bool mask[DOTW][DOTH];
bool primes[dots + 1];

void print_consts()
{
   fprintf(stderr, "inches: %d\n", inches);
   fprintf(stderr, "DPS: %d\n", DPI);
   fprintf(stderr, "dotw and doth: %d %d\n", dotw, doth);
   fprintf(stderr, "W and H: %d %d\n", W, H);
   fprintf(stderr, "DOTW and DOTH: %d %d\n", DOTW, DOTH);
   fprintf(stderr, "dots: %d\n", dots);
}

void print_mask()
{
   for (int i = 0; i < DOTW; ++i)
   {
      for (int j = 0; j < DOTH; ++j)
      {
         int x = mask[i][j] ? 1 : 0;
         fprintf(stderr, "%d ", x);
      }
      fprintf(stderr, "\n");
   }
}

void gen_primes()
{
   fill(primes, primes + dots + 1, true);
   primes[0] = false;
   primes[1] = false;

   for (int i = 2; i < sqrt(dots + 2); ++i)
   {
      if (not primes[i]) continue;
      for (int j = 2*i; j < dots + 1; j += i)
      {
         primes[j] = false;
      }
   }
}

void gen_mask()
{
   int x = DOTW/2;
   int y = DOTH/2;

   int stepx = 1;
   int stepy = 1;
   int dir = 2;
   int j = 0;

   for (int i = 0; i < dots; ++i)
   {
      mask[x][y] = primes[i + 1];
      if (dir == 1)
      {
         if (stepx % 2 == 0)
            ++x;
         else
            --x;
         ++j;
         if (j >= stepx)
         {
            dir = 2;
            ++stepx;
            j = 0;
         }
      }
      else
      {
         if (stepy % 2 == 0)
            --y;
         else
            ++y;
         ++j;
         if (j >= stepy)
         {
            dir = 1;
            ++stepy;
            j = 0;
         }
      }
   }
}

tuple<int, int, int> get_color(int id)
{
   switch(id)
   {
      case 0:
         return make_tuple(1, 0, 0);
      case 1:
         return make_tuple(2, 0, 0);
      case 2:
         return make_tuple(3, 0, 0);
      case 3:
         return make_tuple(3, 1, 1);
      default:
         return make_tuple(4, 4, 4);
   }
}

int main()
{
   gen_primes();
   gen_mask();

   // Setup
   /* // 12 x 12
   vector<int> dot_data = {
      4, 3, 3, 2, 2, 2, 2, 2, 2, 3, 3, 4,
      3, 3, 2, 2, 1, 1, 1, 1, 2, 2, 3, 3,
      3, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 3,
      2, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 2,
      2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2,
      2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2,
      2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2,
      2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2,
      2, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 2,
      3, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 3,
      3, 3, 2, 2, 1, 1, 1, 1, 2, 2, 3, 3,
      4, 3, 3, 2, 2, 2, 2, 2, 2, 3, 3, 4
   };
   //*/
   //* // 6 x 6
   vector<int> dot_data = {
      4, 3, 2, 2, 3, 4,
      3, 1, 0, 0, 1, 3,
      2, 0, 0, 0, 0, 2,
      2, 0, 0, 0, 0, 2,
      3, 1, 0, 0, 1, 3,
      4, 3, 2, 2, 3, 4,
   };
   //*/
   /* // 5 x 5
   vector<int> dot_data = {
      0, 0, 0, 0, 0,
      0, 0, 1, 0, 0,
      0, 1, 1, 1, 0,
      0, 0, 1, 0, 0,
      0, 0, 0, 0, 0,
   };
   //*/
   /* // 4 x 4
   vector<int> dot_data = {
      0, 0, 0, 0,
      0, 1, 1, 0,
      0, 1, 1, 0,
      0, 0, 0, 0,
   };
   //*/
   map<int, map<int, int>> dot_map;
   for (int i = 0, j = 0; i < dot_data.size(); ++i)
   {
      if (i != 0 and i % dotw == 0) ++j;
      dot_map[j][i % dotw] = dot_data[i];
   }

   // PGM Generation
   int white = 4;
   int r, g, b;

   printf("P3\n");
   printf("%d %d\n", W, H);
   printf("%d\n", white);
   for (int i = 0; i < dotw/2; ++i)
   {
      for (int j = 0; j < H; ++j)
      {
         tie(r, g, b) = get_color(white);
         printf("%d %d %d", r, g, b);
         if (j + 1 != H) printf(" ");
      }
      printf("\n");
   }
   int u = 0, v = 0;
   int dx = 0, dy = 0, dotrows = 0;
   for (int i = dotw/2; i < W - dotw/2; ++i)
   {
      for (int j = 0; j < doth/2; ++j)
      {
         tie(r, g, b) = get_color(white);
         printf("%d %d %d ", r, g, b);
      }
      for (int j = doth/2; j < H - doth/2; ++j)
      {
         if (mask[dx][dy])
            tie(r, g, b) = get_color(dot_map[u][v]);
         else
            tie(r, g, b) = get_color(white);
         printf("%d %d %d ", r, g, b);
         if (v + 1 == doth)
            dy = (dy + 1) % DOTH;
         v = (v + 1) % doth;
      }
      for (int j = H - doth/2; j < H; ++j)
      {
         tie(r, g, b) = get_color(white);
         printf("%d %d %d", r, g, b);
         if (j + 1 != H) printf(" ");
      }
      printf("\n");
      if (u + 1 == dotw)
      {
         fprintf(stderr, "Row %d Completed, of %d rows.\n", dotrows++, DOTW);
         dx = (dx + 1) % DOTW;
      }
      u = (u + 1) % dotw;

   }
   for (int i = W - dotw/2; i < W; ++i)
   {
      for (int j = 0; j < H; ++j)
      {
         tie(r, g, b) = get_color(white);
         printf("%d %d %d", r, g, b);
         if (j + 1 != H) printf(" ");
      }
      printf("\n");
   }

   print_consts();
}
