#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define and &&
#define not !

const int inches = 8;

// Target DPI: 300
const int dotw = 15;
const int doth = 15;

const int W = inches*300 - dotw;
const int H = inches*300 - doth;

const int dots = (W/dotw)*(H/doth);

int image[W][H];
bool mask[W/dotw][H/doth];
bool primes[dots + 1];

void print_mask()
{
   for (int i = 0; i < W/dotw; ++i)
   {
      for (int j = 0; j < H/doth; ++j)
      {
         cout << mask[i][j] << " ";
      }
      cout << endl;
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
   int x = W/dotw/2;
   int y = H/doth/2;

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

int main()
{
   gen_primes();
   gen_mask();

   // Setup
   vector<int> dot_data = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
      0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
      0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   map<int, map<int, int>> dot_map;
   for (int i = 0, j = 0; i < dot_data.size(); ++i)
   {
      if (i != 0 and i % dotw == 0) ++j;
      dot_map[j][i % dotw] = dot_data[i];
   }

   // PGM Generation
   cout << "P1" << endl;
   cout << W << " " << H << endl;
   for (int i = 0, dx = 0; i < W; i += dotw, ++dx)
   {
      for (int j = 0, dy = 0; j < H; j += doth, ++dy)
      {
         for (int x = 0; x < dotw; ++x)
         {
            for (int y = 0; y < doth; ++y)
            {
               int I = i + x;
               int J = j + y;
               if (mask[dx][dy])
                  image[I][J] = dot_map[x][y];
               else
                  image[I][J] = 0;
            }
         }
      }
      cerr << "Row " << (dx + 1) << " Completed, of " << (W/dotw) << " rows." << '\n';
   }

   for (int i = 0; i < W; ++i)
   {
      for (int j = 0; j < H; ++j)
      {
         cout << image[i][j];
         if (j + 1 != H)
            cout << " ";
      }
      cout << '\n';
      cerr << "Pixel row " << (i + 1) << " Written, of " << W << " rows." << '\n';
   }
}
