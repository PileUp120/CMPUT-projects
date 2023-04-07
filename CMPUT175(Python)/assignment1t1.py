# reads a flie and returns a list with its individual lines as lists, split by separator
def returnList(name,separator):
    fileName = open(name+'.txt','r')
    fileContent = fileName.read()
    fileName.close()
    fileLines = fileContent.splitlines()
    for e in fileLines:
        e.strip()
    fileList = []
    for i in fileLines:
        listed = i.split(separator)
        fileList.append(listed)
    return fileList
def formatPhone(theList,pos):
    for i in theList:
        i[pos] =list(i[pos])
        i[pos].insert(0,'(')
        i[pos].insert(4,')')
        i[pos].insert(5,' ')
        i[pos].insert(9,' ')
        i[pos] = ''.join(i[pos])
    return theList
def isolatePhnPay(theList):
    condensedList = []
    for i in theList:
        if i[2] not in condensedList:
            condensedList.append(i[2])
    for e in condensedList:
        base = [e]
        condensedList[condensedList.index(e)] = base
    for i in condensedList:
        for e in theList:
            if e[2] == i[0]:
                i.append(float(e[1]))
    condensedList.sort()
    return condensedList
# gets a list from each of the three input files using user defined function "returnList"
familiesList = returnList('families',',')
duesList = returnList('dues',';')
paymentsList = returnList('payments',';')
familiesList = formatPhone(familiesList,0)
duesList = formatPhone(duesList,2)
paymentsList = formatPhone(paymentsList,2)
# creates a new list and appends the phone numbers in dues to the list, without duplicates
# then appends each due to the list to their appropriate phone number
duesCondensed = isolatePhnPay(duesList)
paymentsCondensed = isolatePhnPay(paymentsList)
finalList = []
for i in duesCondensed:
    finalList.append([i[0],sum(i[1:len(i)])])
for i in paymentsCondensed:
    for e in finalList:
        if i[0] == e[0]:
            e.append(sum(i[1:len(i)]))
for i in finalList:
    if (i[1]-i[2]) >= 100:
        i.insert(2,(0.01*(i[1]-i[2])))
    else:
        i.insert(2,' ')
for i in finalList:
    i[1] = round(i[1],2)
    if i[2] != ' ':
        i[2] = round(i[2],2)
for i in familiesList:
    for e in finalList:
        if i[0] == e[0]:
            e.insert(1,i[1])
for i in paymentsList:
    for e in finalList:
        if i[2] == e[0]:
            e.append([i[0],float(i[1])])
fullDue = 0
for i in finalList:
    if (i[2]-i[4]) >=0:
        fullDue += (i[2]-i[4])
for i in finalList:
    if i[3] != ' ':
        fullDue += i[3]
fullInterest = 0
for i in finalList:
    if i[3] != ' ':
        fullInterest += i[3]    
outfile = open('summary.txt','w')
outfile.write('+--------------+------------------+--------+-----+\n')
print('+--------------+------------------+--------+-----+')
outfile.write('| Phone Number | Name             | Due    | Int |\n')
print('| Phone Number | Name             | Due    | Int |')
outfile.write('+--------------+------------------+--------+-----+\n')
print('+--------------+------------------+--------+-----+')
for i in finalList:
    dueValue = 0
    if (i[2]-i[4]) < 100:
        dueValue = i[2]-i[4]
    elif (i[2] - i[4]) <= 0:
        dueValue = 0
    else:
        dueValue = i[2]-i[4]+i[3]
    payString =''
    sideList = i[5:len(i)]
    for e in sideList:
        formtd = ' {0:s} (${1:.2f});'.format(e[0],e[1])
        payString += formtd
    if i[3] != ' ' and (i[2]-i[4]) < 500:
        outfile.write('|{0:s}|{1:18.18s}|${2:7.2f}|${3:4.2f}|[{4:.2f}]'.format(i[0],i[1],dueValue,i[3],i[4]) + payString + '\n')
        print('|{0:s}|{1:18.18s}|${2:7.2f}|${3:4.2f}|[{4:.2f}]'.format(i[0],i[1],dueValue,i[3],i[4]),payString)
    elif (i[2]-i[4]) <= 0 and i[3] == ' ':
        outfile.write('|{0:s}|{1:18.18s}|${2:7.2s}|${3:4s}|[{4:.2f}]'.format(i[0],i[1],'',i[3],i[4]) + payString + '\n')
        print('|{0:s}|{1:18.18s}|${2:7.2s}|${3:4s}|[{4:.2f}]'.format(i[0],i[1],'',i[3],i[4]),payString)
    elif (i[2]-i[4]) >= 500:
        outfile.write('|{0:s}|**{1:16.16s}|${2:7.2f}|${3:4.2f}|[{4:.2f}]'.format(i[0],i[1],dueValue,i[3],i[4]) + payString + '\n')
        print('|{0:s}|**{1:16.16s}|${2:7.2f}|${3:4.2f}|[{4:.2f}]'.format(i[0],i[1],dueValue,i[3],i[4]),payString)
    else:
        outfile.write('|{0:s}|{1:18.18s}|${2:7.2f}|${3:4s}|[{4:.2f}]'.format(i[0],i[1],dueValue,i[3],i[4]) + payString + '\n')
        print('|{0:s}|{1:18.18s}|${2:7.2f}|${3:4s}|[{4:.2f}]'.format(i[0],i[1],dueValue,i[3],i[4]),payString)
outfile.write('+--------------+------------------+--------+-----+\n')
print('+--------------+------------------+--------+-----+')
outfile.write('| {0:13.13s}|${1:26.2f}|\n'.format('Total Dues',fullDue))
print('| {0:13.13s}|${1:26.2f}|'.format('Total Dues',fullDue))
outfile.write('| {0:13.13s}|${1:26.2f}|\n'.format('Total Interest',fullInterest))
print('| {0:13.13s}|${1:26.2f}|'.format('Total Interest',fullInterest))
outfile.close()