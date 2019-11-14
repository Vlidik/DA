#include <iostream>
#include <vector>

void Swap (std::vector<int> &v, int x, int y)
{
	v[y] += v[x];
	v[x]  = v[y] - v[x];
	v[y] -= v[x];
}

int main() {
	int n;
	const int N = 4;

	std::cin >> n;
	std::vector <int> x(n);

	for (int i = 0; i < n; i++) {
		std::cin >> x[i];
	}

	std::vector <int> count(N);

	for (int i : x)
		count[i]++;

	count[3] = count[2] + count[1];
	count[2] = count[1] + count[0];
	count[1] = count[0];

	int res = 0;

	for (int j = 0; j < n; j++) {
		if (j < count[2]) {
			if (x[j] == 3) {
				for (int k = n - 1; k >= count[2]; k--) {
					if (x[k] == 1) {
						Swap(x, j, k);
						res++;
						break;
					}
				}
			} else if (x[j] == 2) {
				for (int k = count[2]; k < n; k++) {
					if (x[k] == 1) {
						Swap(x, j, k);
						res++;
						break;
					}
				}
			}
		} else if (j < count[3] && x[j] == 3) {
			for (int k = count[3]; k < n; k++) {
				if (x[k] == 2) {
					Swap(x, j, k);
					res++;
					break;
				}
			}
		}
	}

	std::cout << res << std::endl;

	return 0;
}
