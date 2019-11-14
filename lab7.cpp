#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> x(n+1);
    std::vector<int> y(n+1);

    for(int i = 2; i <= n; ++i){
        x[i] = x[i-1] + i;
        y[i] = 1;

        if(i % 2 == 0 && x[i / 2] + i < x[i]){
            x[i] = x[i/2] + i;
            y[i] = 2;
        }

        if(i % 3 == 0 && x[i / 3] + i < x[i]){
            x[i] = x[i/3] + i;
            y[i] = 3;
        }
    }

    std::cout << x.back() << "\n";

    while (n > 1) {
		if (y[n] == 1) {
			std::cout << "-1";
			n--;
		}
		else if (y[n] == 2) {
			std::cout << "/2";
			n /= 2;
		}
		else {
			std::cout << "/3";
			n /= 3;
		}
		if (n != 1) std::cout << " ";
	}
	std::cout << "/n";

    return 0;
}
