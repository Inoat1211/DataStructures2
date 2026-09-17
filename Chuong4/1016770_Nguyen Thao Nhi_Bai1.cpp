#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
using namespace std;
int hashInt(int key, int m) {
// TODO: xu ly dung ca truong hop key am, ket qua phai thuoc [0, m-1]
int result= key%m;
if(result<0) result += m;
return result;
}
long long hashString(const string& s, int m) {
const int p = 31;
const long long mod = 1e9 + 9;
// TODO: tham khao lai cong thuc Polynomial Rolling Hash o muc 4.1.3
long long hash =0;
long long power = 1;
for(int i=0;i<(int)s.length();i++)
{
int value =s[i] - 'a' + 1;
hash = (hash + value * power) % mod;
power = (power * p) % mod;
}
return hash % m;
}

double calculateMean(const vector<int>& buckets)
{
double sum = 0;
for (int i = 0; i < (int)buckets.size(); i++)
{
 sum += buckets[i];
 }
return sum / buckets.size();
}

double calculateStandardDeviation(const vector<int>& buckets)
{
double mean = calculateMean(buckets);
double sum = 0;
for (int i = 0; i < (int)buckets.size(); i++)
{
double difference = buckets[i] - mean;
sum += difference * difference;
 }
 return sqrt(sum / buckets.size());
}

void evaluateRandomKeys(mt19937& rng, int numKeys, int m)
{
 vector<int> buckets(m, 0);
 uniform_int_distribution<int> distribution(-1000000000, 1000000000);
 for (int i = 0; i < numKeys; i++)
 {
  int key = distribution(rng);
  int index = hashInt(key, m);
  buckets[index]++;
 }
 double mean = calculateMean(buckets);
 double standardDeviation = calculateStandardDeviation(buckets);
 int minBucket = buckets[0];
 int maxBucket = buckets[0];
 for (int i = 1; i < m; i++)
 {
  if (buckets[i] < minBucket)
  {
   minBucket = buckets[i];
  }
  if (buckets[i] > maxBucket)
  {
   maxBucket = buckets[i];
  }
 }
 cout << "m = " << m << endl;
 cout << "Gia tri trung binh: " << mean << endl;
 cout << "Do lech chuan: " << standardDeviation << endl;
 cout << "Bucket it phan tu nhat: " << minBucket << endl;
 cout << "Bucket nhieu phan tu nhat: " << maxBucket << endl;
 cout << endl;
}

void evaluateMultiplesOfTen(int numKeys, int m)
{
 vector<int> buckets(m, 0);
 for (int i = 0; i < numKeys; i++)
 {
  int key = i * 10;
  int index = hashInt(key, m);
  buckets[index]++;
 }
 int usedBuckets = 0;
 for (int i = 0; i < m; i++)
 {
  if (buckets[i] > 0)
  {
   usedBuckets++;
  }
 }
 cout << "m = " << m << endl;
 cout << "So bucket duoc su dung: "
 << usedBuckets << "/" << m << endl;
 cout << "Ty le su dung: "
 << usedBuckets * 100.0 / m << "%" << endl;
 cout << endl;
}

int main() {
mt19937 rng(42);
int numKeys = 100000;
int m1 = 97, m2 = 100;
// TODO Phan B.1: sinh 100000 khoa ngau nhien, bam vao bang m1 va m2,
// dem so phan tu moi bucket, tinh trung binh + do lech chuan
 cout << "DANH GIA KHOA NGAU NHIEN" << endl;
 evaluateRandomKeys(rng, numKeys, m1);
 evaluateRandomKeys(rng, numKeys, m2);
// TODO Phan B.2: sinh 100000 khoa la boi so cua 10, bam vao bang m1 va m2,
// dem so bucket duoc su dung (khac 0) trong moi truong hop
 cout << "DANH GIA KHOA BOI SO CUA 10" << endl;
 evaluateMultiplesOfTen(numKeys, m1);
 evaluateMultiplesOfTen(numKeys, m2);
return 0;
}
