def longest_subarray(N, K, arr):
    left = 0
    curr_sum = 0
    max_length = 0

    for right in range(N):
        curr_sum += arr[right]

        while curr_sum > K and left <= right:
            curr_sum -= arr[left]
            left += 1

        max_length = max(max_length, right - left + 1)

    return max_length

# Example usage
N = 5
K = 4
arr = [4, 1, 2, 1, 5]
print(longest_subarray(N, K, arr))  # Output: 3

N = 5
K = 5
arr = [1, 1, 1, 1, 1]
print(longest_subarray(N, K, arr))  # Output: 5
