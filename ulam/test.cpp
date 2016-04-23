#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

#ifdef _MSC_VER
#define and &&
#define not !
#endif

const int inches = 1;

// Target DPI: 300
const int DPI = 600;
const int dotw = 6;
const int doth = 6;

const int W = inches*DPI;
const int H = inches*DPI;

const int DOTW = W/dotw - 1;
const int DOTH = H/doth - 1;

const int dots = DOTW*DOTH;

int image[W][H];
bool mask[DOTW][DOTH];
bool primes[dots + 1];

void print_consts()
{
   cerr << "inches: " << inches << endl;
   cerr << "DPI: " << DPI << endl;
   cerr << "dotw and doth: " << dotw << " " << doth << endl;
   cerr << "W and H: " << W << " " << H << endl;
   cerr << "DOTW and DOTH: " << DOTW << " " << DOTH << endl;
   cerr << "dots: " << dots << endl;
}

void print_mask()
{
   for (int i = 0; i < DOTW; ++i)
   {
      for (int j = 0; j < DOTH; ++j)
      {
         cerr << mask[i][j] << " ";
      }
      cerr << endl;
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

struct iofix
{
   ios_base::Init i;
   iofix() {
      cin.sync_with_stdio(0);
      cin.tie(0);
   }
} iofix;

int main()
{
   gen_primes();
   gen_mask();

   // Setup
   /* // 12 x 12
   vector<int> dot_data = {
      3, 3, 3, 2, 2, 2, 2, 2, 2, 3, 3, 3,
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
      3, 3, 3, 2, 2, 2, 2, 2, 2, 3, 3, 3
   };
   //*/
   //* // 6 x 6
   vector<int> dot_data = {
      4, 4, 3, 3, 4, 4,
      4, 2, 1, 1, 2, 4,
      3, 1, 0, 0, 1, 3,
      3, 1, 0, 0, 1, 3,
      4, 2, 1, 1, 2, 4,
      4, 4, 3, 3, 4, 4,
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

   cout << "P2" << endl;
   cout << W << " " << H << endl;
   cout << white << endl;
   for (int i = 0; i < dotw/2; ++i)
      for (int j = 0; j < H; ++j)
         image[i][j] = white;
   int u = 0, v = 0;
   int dx = 0, dy = 0;
   for (int i = dotw/2; i < W - dotw/2; ++i)
   {
      for (int j = 0; j < doth/2; ++j)
         image[i][j] = white;
      for (int j = doth/2; j < H - doth/2; ++j)
      {
         if (mask[dx][dy])
            image[i][j] = dot_map[u][v];
         else
            image[i][j] = white;
         if (v + 1 == doth)
            dy = (dy + 1) % DOTH;
         v = (v + 1) % doth;
      }
      for (int j = H - doth/2; j < H; ++j)
         image[i][j] = white;
      if (u + 1 == dotw)
         dx = (dx + 1) % DOTW;
      u = (u + 1) % dotw;
      cerr << "Row " << (dx + 1) << " Completed, of " << (W/dotw) << " rows." << '\n';
   }
   for (int i = W - dotw/2; i < W; ++i)
      for (int j = 0; j < H; ++j)
         image[i][j] = white;

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

   print_consts();
   print_mask();
}
