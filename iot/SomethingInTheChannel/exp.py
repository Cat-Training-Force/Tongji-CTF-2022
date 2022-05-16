"""
MiaoTony
"""

filename = 'file.txt'
data = ''
with open(filename, 'r', encoding='utf-8') as f:
    while True:
        line = f.readline()
        if not line:
            break
        # print(line)
        s = line.split('TX: ')[1]
        if s.startswith('Stop') or s.startswith('Start'):
            continue
        s = s[:-1]  # remove '\n'
        # print(line, s, len(s))
        if len(s) > 1 and s[0] == '[' and s[-1] == ']':
            s = s[1:-1]
        else:
            s = hex(ord(s))[2:].rjust(2, '0')
        # print(s)
        data += s

print(data)
file = bytes.fromhex(data)
with open('out.zip', 'wb') as f:
    f.write(file)
