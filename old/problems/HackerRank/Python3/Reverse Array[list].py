if __name__ == '__main__':
    n = int(input())

    arr = list(map(int, input().rstrip().split()))
    string = ""
    arr.reverse()
    for l in arr:
        if (len(string) == 0):
            string = str(l)
        else: 
            string = string+" "+str(l)

    print(string)
