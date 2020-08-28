f1 = open('/Users/roblusk/Documents/College/Database Management/Project #2/Data/expendatureMaster.csv', 'r')
f2 = open('expendatureMaster.sql', 'w')
a = f1.readline()
while a:
    if "\\" in a:
        a = a.replace("\\","")
    if "'" in a:
        a = a.replace("'", "\\'")
    a = a.split('|')
    a = "\',\'".join(a)
    f2.write('''INSERT INTO expendatureMaster VALUE('%s');\n''' %(a))
    a = f1.readline()
f1.close()
f2.close()