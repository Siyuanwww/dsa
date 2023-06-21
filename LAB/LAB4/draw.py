def genNext(str, improved = False):
    str += '*'
    n = len(str)
    str += '^'
    j = 0
    t = -1
    nxt = list([-1])
    while j < n:
        if t < 0 or str[j] == str[t]:
            j = j + 1
            t = t + 1
            if improved:
                if str[j] == str[t]:
                    nxt.append(nxt[t])
                else:
                    nxt.append(t)
            else:
                nxt.append(t)
        else:
            t = nxt[t]
    return nxt

def genAuto(str, nxt):
    n = len(str)
    str += '*'
    trans = list()
    cur = list([0] * 26)
    cur[ord(str[0]) - ord('a')] = 1
    trans.append(cur)
    for i in range(0, n): # 状态 i + 1 的转移
        # abcdefg
        # i = 0
        #
        cur = list([0] * 26)
        for j in range(0, 26):
            if j == ord(str[i + 1]) - ord('a'):
                cur[j] = i + 2
                # print("i = %d, hit j = %d" % (i, j))
            else:
                if nxt[i + 1] <= 0:
                    cur[j] = trans[0][j]
                else:
                    cur[j] = trans[nxt[i + 1]][j]
                # cur[j] = trans[nxt[i + 1]]
        # i = 3, j = 'b'
        trans.append(cur)
    return trans

# str = "ababac"
nxt = genNext("ababac", improved=False)
trans = genAuto("ababac", nxt)

print(nxt)
for i in range(0, len(trans)):
    trans[i] = trans[i][0:3]
print(trans)