#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <stdint.h>
using namespace std;


const int L1D_CACHE_SIZE = 32768;

//Generate primes using the segmented sieve of Eratosthenes.
// This algorithm uses O(n log log n) operations and O(sqrt(n)) space.


void segmented_sieve(int64_t limit)
{
  int sqrt = (int) std::sqrt(limit);
  int segment_size = max(sqrt, L1D_CACHE_SIZE);

  int64_t count = (limit < 2) ? 0 : 1;
  int64_t s = 3;
  int64_t n = 3;

  // generate small primes <= sqrt
  vector<char> is_prime(sqrt + 1, 1);
  for (int i = 2; i * i <= sqrt; i++)
    if (is_prime[i])
      for (int j = i * i; j <= sqrt; j += i)
        is_prime[j] = 0;

  // vector used for sieving
  vector<char> sieve(segment_size);
  vector<int> primes;
  vector<int> next;

  for (int64_t low = 0; low <= limit; low += segment_size)
  {
    fill(sieve.begin(), sieve.end(), 1);

    // current segment = interval [low, high]
    int64_t high = min(low + segment_size - 1, limit);

    // add new sieving primes <= sqrt(high)
    for (; s * s <= high; s += 2)
    {
      if (is_prime[s])
      {
        primes.push_back((int) s);
          next.push_back((int)(s * s - low));
      }
    }

    // sieve the current segment
    for (size_t i = 0; i < primes.size(); i++)
    {
      int j = next[i];
      for (int k = primes[i] * 2; j < segment_size; j += k)
        sieve[j] = 0;
      next[i] = j - segment_size;
    }

    for (; n <= high; n += 2)
      if (sieve[n - low]) // n is a prime
        count++;

	cout<<primes[primes.size()-1]<<endl;

  }

  //cout<<primes[0]<<endl;

	FILE *ff=fopen("primes.txt","w");

	for (size_t i = 0; i < primes.size(); i++)
	{
		fprintf(ff,"%d",primes[i]);
		fprintf(ff,"\r\n");
	}

}

int main()
{
    segmented_sieve(100000000000000);

  return 0;
}