import collections
dic = collections.defaultdict(lambda:-1)
while True:
    raw = input()
    if raw[0]=='E':
        break
    if raw[0]=='I':
        _,value,key=raw.split()
        dic[key]=value
    else:
        _,key=raw.split()
        print(dic[key])





