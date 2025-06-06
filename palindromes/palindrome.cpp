#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {

    // Init
    std::string s = argv[1];
    int n = s.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    // Init diagonal
    for (size_t i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }

    for (int l = 2; l < n + 1; ++l) {
        for (int i = 0; i < n - l + 1; ++i) {
            int j = i + l - 1;
            if (s[i] == s[j]) {
                if (i + 1 <= j - 1) {
                    dp[i][j] = dp[i][j - 1] + 2;
                } else {
                    dp[i][j] = 2;
                }
            } else {
                dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    // Print DP
    for (size_t i = 0; i < dp.size(); ++i) {
        // Iterate through elements in the current row
        for (size_t j = 0; j < dp[i].size(); ++j) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << std::endl;  // Move to the next line after each row
    }

    std::cout << "The longest subseq palindrome is: " << dp[0][n - 1] << std::endl;

    return 0;
}