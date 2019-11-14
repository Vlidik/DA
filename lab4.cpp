#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <exception>

int pat_len = 0;
int RANGE = 498;
int BUFSIZE = 500;
bool full = 0;
int countStr = 1;
int countWord = 0;


void GetPattern(std::vector<std::pair<int, std::pair<int,int> > >& patternt) {
    bool spaceCounter = 1;
    int word = 0;
    char c;
    c = getchar();
    while (c != '\n') {
        if (c >= '0' && c <= '9') {
            word *= 10;
            word += (c - '0');
            spaceCounter = 0;
        } else if (c == ' '){
            if (!spaceCounter) {
                patternt.emplace_back(std::make_pair(word, std::make_pair(0,0)));
            }
            spaceCounter = 1;
            word = 0;
        }
        c = getchar();
    }
    if (!spaceCounter) {
        patternt.emplace_back(std::make_pair(word, std::make_pair(0,0)));
    }
}

void GetText(std::vector< std::pair<int, std::pair<int,int> > >& textBuf,int bufferSize) {
    int word = 0;
    full = 0;
    int size = textBuf.size();
    bool spaceCounter = 1;
    char c;
    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9') {
            word *= 10;
            word += (c - '0');
            spaceCounter = 0;
        } else if (c == ' ' && !spaceCounter) {
            ++countWord;
            textBuf.emplace_back(std::make_pair(word, std::make_pair(countWord, countStr)));
            ++size;
            word = 0;
            spaceCounter = 1;
            if (size == bufferSize) {
                full = 1;
                break;
            }
        } else if (c == '\n') {
            if (!spaceCounter) {
                ++countWord;
                textBuf.emplace_back(std::make_pair(word, std::make_pair(countWord, countStr)));
                ++size;
                spaceCounter = 1;
            }
            ++countStr;
            word = 0;
            countWord = 0;
            if (size == bufferSize) {
                full = 1;
                break;
            }
        }
    }
}


void Z_function(std::vector<std::pair<int, std::pair<int,int> > >& vec, std::vector<std::pair<int,int> >& res) {
    int n = 0;
    if (full) {
        n = (RANGE + 1) * pat_len;
    } else {
        n = vec.size();
    }
    if (n <= 0) return;
    std::vector<int> z (n);
    int r = 0;
    int l = 0;
    int t = 0;
    int k2;

    for (int k = 1; k < n; ++k) {
        if (k > r) {
            int j = 0;
            while (z[k] < pat_len && vec[k + j].first == vec[j].first) {
                ++z[k];
                ++j;
            }
            if (z[k] > 0) {
                r = k + z[k] - 1;
                l = k;
            }

        } else {
            k2 = k - l;
            if (z[k2] < r - k + 1) {
                z[k] = z[k2];
            } else {
                z[k] = r - k + 1;
                t = 0;
                while (z[k] < pat_len && vec[r - k + 1 + t].first == vec[k + r - k + 1 + t].first) {
                    z[k]++;
                    ++t;
                }
                r = k + z[k] - 1;
                l = k;
            }
        }
        if (z[k] >= pat_len && k >= pat_len) {
            res.emplace_back( std::make_pair( (vec[k].second).first, (vec[k].second).second ));
        }
    }
}

int main() {

    std::vector<std::pair<int, std::pair<int,int> > > pat;
    GetPattern(pat);
    try {
        if (pat.size() <= 0) {
            throw -1;
        }
    } catch (int t) {
        return t;
    }

    pat_len = pat.size();
    int bufferSize = BUFSIZE * pat.size();
    GetText(pat, bufferSize);
    std::vector< std::pair<int,int> > res;
    while (full) {
        Z_function(pat, res);

        pat.erase(pat.begin() + pat_len, pat.begin() + RANGE * pat_len + 1);
        GetText(pat, bufferSize);
    }
    Z_function(pat, res);
    for(int i = 0; i < res.size(); i++) {
        std::cout << res[i].second << ", " << res[i].first << std::endl;
    }
    return 0;
}
