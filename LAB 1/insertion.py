def lexi(name_i, name_j):
    for i, j in zip(name_i, name_j):
        if ord(j) > ord(i):
            return True
        elif ord(j) < ord(i):
            return False
    return len(name_j) > len(name_i)
 
def lexi_time(time_i, time_j):
    h_i, m_i = map(int, time_i.split(":"))
    h_j, m_j = map(int, time_j.split(":"))
    return (h_j, m_j) > (h_i, m_i)
 
n = int(input())
arr = []
for i in range(n):
    arr.append(input())
 
for i in range(1, n):
    in_parts = arr[i].split()
    name_i, time_i = in_parts[0], in_parts[6]
    for j in range(i-1, -1, -1):
        flag = False
        in_parts = arr[j].split()
        name_j, time_j = in_parts[0], in_parts[6]
        if name_i != name_j:
            if lexi(name_i, name_j):
                arr[i], arr[j] = arr[j], arr[i]
                flag = True
        else:
            if time_i != time_j:
                if lexi_time(time_i, time_j) == False:
                    arr[i], arr[j] = arr[j], arr[i]
                    flag = True
        i = i - 1
        if flag == False:
            break

for i in arr:
    print(i)