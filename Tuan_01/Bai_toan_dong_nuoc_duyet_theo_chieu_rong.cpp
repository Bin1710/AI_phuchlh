#include <iostream>
#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

typedef pair < int, int > jugs; //define structure data for jugs
void BFS(int a, int b, int target); //define BFS function
void printpath(map < jugs, jugs > mp, jugs u); //define function print results


int main() {
  
  int a;
  int b;
  int target;
  /// viet ham nhap a,b, target tu ban phim
  cin>>a;
  cin>>b;
  cin>>target;
  if (a<target && b<target) cout<<"No solution";
  else
    BFS(a,b,target);
  return 0;
}

void printpath(map < jugs, jugs > mp, jugs u) {
  if (u.first == 0 && u.second == 0) {
    cout << 0 << " " << 0 << endl;
    return;
  }
  printpath(mp, mp[u]);
  cout << u.first << " " << u.second << endl;
}

void BFS(int a, int b, int target) {
  map < jugs, int > m; // kiem tra cac node da duyet: 1 da duyet, 0 chua duyet (default = 0)
  bool isSolvable = false;  // ton tai ket qua
  map < jugs, jugs > mp; // Graph 
  queue < jugs > q; // Queue de duyet cay bang BFS 


  q.push(make_pair(0, 0)); // Bat dau duyet cay cho ket qua vao hanh doi 
  while (!q.empty()) 
  {
    jugs u = q.front(); //lay phan tu dau tien
    q.pop(); // xoa phan tu dau tien khoi hang doi
    if (m[u] == 1) // node da duyet thi pass 
      continue;
    m[{u.first,u.second}] = 1; // da duyet

    if (u.first == target || u.second == target) {
      isSolvable = true;

      printpath(mp, u);
      if (u.first==target && u.second!=0)
        cout<<u.first<<" 0";
      else if (u.second==target && u.first!=0)
        cout<<"0 "<<u.second;
      return;
    }
    // ======= Operation =====
    // fill into jug 1
    if (m[{a,u.second}] != 1) { 
      q.push({a,u.second});
      mp[{a,u.second}] = u;
    }
    // fill into jug 2
    if (m[{u.first,b}] != 1) { 
      q.push({u.first,b});
      mp[{u.first,b}] = u;
    }
    // ## Transfer of water 
    int d = b - u.second; // from jug 1 to jug 2
    if (u.first >= d) {
      int c = u.first - d; // transfer a little 
      if (m[{c,b}] != 1) {q.push({c,b});
        mp[{c,b}] = u;
      }
    } else {
      int c = u.first + u.second;
      if (m[{0,c}] != 1) { /// transfer all 
        q.push({0,c});
        mp[{0,c}] = u;
      }
    }

    // from jug 2 to j1
    int e = a - u.first; // from jug 2 to jug 1
    if (u.second >= e) {
      int c = u.second - e; // transfer a little 
      if (m[{a,c}] != 1) {q.push({a,c});
        mp[{a,c}] = u;
      }
    } else {
      int c = u.first + u.second;
      if (m[{c,0}] != 1) { /// transfer all 
        q.push({c,0});
        mp[{c,0}] = u;
      }
    }

    if (m[{u.first, 0}] != 1) {
      q.push({u.first,0});
      mp[{u.first,0}] = u;
    }

    if (m[{0,u.second}] != 1) {
      q.push({0,u.second});
      mp[{0,u.second}] = u;
    }

  }
  if (!isSolvable)
    cout << "No solution";
}
