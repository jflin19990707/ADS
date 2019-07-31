#include <cstdio>
#include <algorithm>

#define SIZE 10001 
#define INF (1 << 14)

int arr[SIZE];
int left_dp1[SIZE], left_dp2[SIZE];
int right_dp1[SIZE], right_dp2[SIZE];

void initDP();
void cal(int N, int *a, int *dp1, int *dp2);

int main(void)
{
    int N;
    /* get input data */
    scanf("%d", &N);
    for (int i = 0; i < N; i ++) {
        scanf("%d", &arr[i]);
    }
    /* calculate the LIS of 'arr' */
    /*'LIS' means the longest  increasing subsequence*/
    cal(N, arr, left_dp1, left_dp2);
    /*
     * D_i of 'arr' = I_i of reverse of 'arr'
     * calculate the LIS of reverse of 'arr'
     */
    std::reverse(arr, arr + N);
    cal(N, arr, right_dp1, right_dp2);

    /* enumerate the index of solution */
    int idx = 0, ans = 0, diff = INF;
    /*ans is the length*/
    for (int i = 0; i < N; i ++) {
        /* check if the solution is legal */
        if (left_dp2[i] <= 1 || right_dp2[N - 1 - i] <= 1) {
            continue;
        }

        int cur_ans = left_dp2[i] + right_dp2[N - 1 - i] - 1;
        int cur_diff = std::abs(left_dp2[i] - right_dp2[N - 1 - i]);

        if (cur_ans > ans || (cur_ans == ans && cur_diff < diff)) {
            ans = cur_ans;
            diff = cur_diff;
            idx = i;
        }
    }
    if (ans > 0) {
        /* 1-index */
        printf("%d %d %d\n", ans, idx + 1, arr[N - 1 - idx]);
    } else {
        printf("No peak shape");
    }
    return 0;
}

void initDP(int *dp)  /*function to initial dp*/
{
    dp[0] = -INF;
    for (int i = 1; i < SIZE; i ++) {
        dp[i] = INF;
    }
}
/*
 *  N      : size of the array
 *  a[i]   : element
 *  dp1[i] : the smallest value of last element of LIS of length i
 *  dp2[i] : the length of LIS whose last element is a[i]
 */
void cal(int N, int *a, int *dp1, int *dp2)
{
    initDP(dp1);

    for (int i = 0; i < N; i ++) {
        /*
         * lower_bound : Find the first number greater than or equal to a[i] 
		 * 				 from the dp1 to the dp1+N-1 , if found than returns
		 * 				 the number's adress , or return the dp1+N if not.
		 */
        int *dp ;
		dp = std::lower_bound(dp1, dp1 + N, a[i]);
        /*
         * update smallest element of LIS of length (l + 1)
         * (*dp = dp[l + 1])
         */
        *dp = std::min(*dp, a[i]);

        /* length of LIS = (dp - dp1) */
        dp2[i] = (int)(dp - dp1);
    }
}
