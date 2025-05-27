import os, sys, time, random, threading, subprocess

# Compile and run: pypy _A1F_Testing.py
def solve(sIDs, sMarks):
    N = len(sIDs)
    cnt = 0
    arr = []
    print( sIDs)
    for i in range(N):
        max_idx = i
        max = sMarks[i]
        flag = False
        print("____________")
        print("LOOP", i)
        for j in range(i+1, N):
            if sMarks[j] > max:
                max_idx = j
                max = sMarks[j]
                flag = True
            elif sMarks[j] == max:
                if sIDs[j]<sIDs[max_idx]:
                    max_idx = j
                    flag = True
        if flag == True:
            print(sMarks[i], sMarks[max_idx])
            sMarks[i], sMarks[max_idx] = sMarks[max_idx], sMarks[i]
            sIDs[i], sIDs[max_idx] = sIDs[max_idx], sIDs[i]
            print(sMarks)
            cnt += 1
        print(sMarks)    
    for i, j in zip(sIDs, sMarks):
        id, mark = i, j
        arr.append((id, mark))
    return (cnt, arr)

N = 0
sIDs, sMarks, res = [], [], []

# stdin
# 7
# 7 4 9 3 2 5 1
# 40 50 50 20 10 10 10
N = int(input())
sIDs = list(map(int, input().split()))
sMarks = list(map(int, input().split()))
start = time.time()
res = solve(sIDs.copy(), sMarks.copy())
print(res)
finish = time.time()
elapsed = finish - start

# # stdout
# print(res)

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)

# # file input
# with open("TimeLimitExceeded.txt") as fin:
# with open("CustomTest.txt") as fin:
# with open("WrongAnswer.txt") as fin:
#     sIDs = list(map(int, fin.readlines()[3][8:-2].split(", ")))
#     sMarks = list(map(int, fin.readlines()[3][10:-2].split(", ")))

# # hardcoded input
# sIDs = [7, 4, 9, 3, 2, 5, 1]
# sMarks = [40, 50, 50, 20, 10, 10, 10]


# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(res))