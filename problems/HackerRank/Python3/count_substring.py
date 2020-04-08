def count_substring(string, sub_string):
    count = 0
    while (len(string)!=0):
        index = string.find(sub_string)
        if (index == -1):
            break
        count+=1
        string = string[index+1:]
    return count

if __name__ == '__main__':
    string = input().strip()
    sub_string = input().strip()
    
    count = count_substring(string, sub_string)
    print(count)