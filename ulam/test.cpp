#include <bits/stdc++.h>

using namespace std;

// Target DPI: 300
const int W = 300;
const int H = 300;

const int dotw = 15;
const int doth = 15;

int image[W][H];

int main()
{
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
      if (i != 0 and i % 15 == 0) ++j;
      dot_map[j][i % 15] = dot_data[i];
   }

///*
   // PGM Generation
   cout << "P1" << endl;
   cout << W << " " << H << endl;
   for (int i = 0; i < W; i += dotw)
   {
      for (int j = 0; j < H; j += doth)
      {
         for (int x = 0; x < dotw; ++x)
         {
            for (int y = 0; y < doth; ++y)
            {
               int I = i + x;
               int J = j + y;
               image[I][J] = dot_map[x][y];
            }
         }
      }
   }

   for (int i = 0; i < W; ++i)
   {
      for (int j = 0; j < H; ++j)
      {
         cout << image[i][j];
         if (j + 1 != H)
            cout << " ";
      }
      cout << endl;
   }
//*/
}
