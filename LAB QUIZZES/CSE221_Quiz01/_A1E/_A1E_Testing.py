import os, sys, time, random, threading, subprocess
# Compile and run: pypy _A1E_Testing.py

def solve(arr):
    # Change the given code
    for i in range(len(arr) - 1):
        for j in range(len(arr) - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr


N = 0
arr, res = [], []

# stdin input
# 5
# 3 2 1 4 5
N = int(input())
arr = list(map(int, input().split()))

# write your code at the solve function
result = solve(arr)


##Time Limit Check Starts
#######################
start = time.time()
res = solve(arr.copy())
finish = time.time()
elapsed = finish - start

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)
#######################
##Time Limit Check Ends


#Other input methods

# # file input
# with open("TimeLimitExceeded.txt") as fin:
# with open("CustomTest.txt") as fin:
# with open("WrongAnswer.txt") as fin:
#     arr = list(map(int, fin.readlines()[3][7:-2].split(", ")))


# # hardcoded input
# arr = [3, 2, 1, 4, 5]


