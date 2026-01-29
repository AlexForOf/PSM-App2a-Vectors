#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

using Vector = vector<double>;

double dotProduct(const Vector &a, const Vector &b)
{
 double sum = 0.0;

 for (size_t i = 0; i < a.size(); ++i)
 {
  sum += a[i] * b[i];
 }

 return sum;
}

Vector scale(const Vector &v, double c)
{
 Vector result = v;
 for (auto &val : result)
 {
  val *= c;
 }
 return result;
}

Vector subtract(const Vector &a, const Vector &b)
{
 Vector result = a;

 for (size_t i = 0; i < a.size(); ++i)
 {
  result[i] -= b[i];
 }

 return result;
}

vector<Vector> gramSchmidt(const vector<Vector> &inputVectors)
{
 vector<Vector> uVectors;
 for (int i = 0; i < inputVectors.size(); ++i)
 {
  Vector v = inputVectors[i];
  Vector u_next = v;

  for (int j = 0; j < i; ++j)
  {
   Vector u_prev = uVectors[j];

   double scalarCoef = dotProduct(u_next, u_prev) / dotProduct(u_prev, u_prev);

   Vector projection = scale(u_prev, scalarCoef);

   u_next = subtract(u_next, projection);
  }

  uVectors.push_back(u_next);
 }

 return uVectors;
}

void printVector(const Vector &v)
{
 cout << "(";
 for (int i = 0; i < v.size(); i++)
  cout << v[i] << (i < v.size() - 1 ? ", " : "");
 cout << ")";
}

int main()
{
 vector<Vector> input = {
     {1.0, 1.0, 0.0},
     {1.0, 0.0, 1.0},
     {0.0, 1.0, 1.0},
     {0.0, 1.0, 1.0}};

 cout << "Original Vectors:\n";
 for (auto v : input)
 {
  printVector(v);
  cout << endl;
 }

 vector<Vector> result = gramSchmidt(input);

 cout << "\nOrthogonal Vectors:\n";
 for (auto v : result)
 {
  printVector(v);
  cout << endl;
 }

 cout << "\nPress Enter to exit...";
 cin.ignore();
 cin.get();
 return 0;
}