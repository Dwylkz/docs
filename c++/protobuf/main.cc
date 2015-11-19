#include <cstdio>
#include <iostream>

#include <main.pb.h>

using namespace std;
using namespace test;

int main(int argc, char** argv)
{
  Test test1;
  test1.set_a("fuck");
  test1.add_c("huhu");

  Test test2;
  test2.set_b("huck");
  test1.add_c("xixi");

  test1.MergeFrom(test2);

  cout << test1.DebugString() << endl;

  return 0;
}
