odd = ""
even = ""
lists = []
num = int(input())
for i in range(0, num):
    string = input()
    for j in range(0, len(string)):
        if j % 2 == 0:
            even += (string+str(i))[j]
        else:
            odd += (string+str(i))[j]
    lists.append(even+" "+odd)
    odd = ""
    even = ""

for l in lists:
    print(l)


