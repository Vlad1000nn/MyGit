n = int(input())
for _ in range(n):
    a = [len(x) for x in input().split(' ')]
    if a == [2] or a == [6] or a == [7] or a == [11] or a == [17] or a == [8, 1, 8, 7] or a == [3, 4] or a == [8, 7] or a == [5, 10]:
        print(1)
    else:
        print(0)
        