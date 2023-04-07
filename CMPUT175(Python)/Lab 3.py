def readList(userInput):
    inList = userInput.split(sep=' ')
    for i in range(len(inList)):
        inList[i] = float(inList[i])
    inList.sort()
    print(inList)
    return inList
def calculateMean(userList):
    listMean = sum(userList)/len(userList)
    print("The Mean is: %f" %(listMean))
    return listMean
def calculateStandardDev(userList,userMean):
    from math import sqrt
    userStdDev = sqrt(sum([(e - userMean)**2 for e in userList]) / (len(userList) - 1))
    print("Std Dev. is: %f" %(userStdDev))
    return userStdDev
def outlier(userList,userMean,userStdDev):
    outliers = []
    for e in userList:
        if e >= (userMean + 3*userStdDev) or e <= (userMean - 3*userStdDev):
            outliers.append(e)
    print("Outliers:",outliers)

enterData = True
while enterData:
    userInput = input("Enter a set of numbers (separated by space):")
    theList = readList(userInput)
    theMean = calculateMean(theList)
    theStdDev = calculateStandardDev(theList,theMean)
    outlier(theList,theMean,theStdDev)
    while True:
        reply = input("Do you want to enter more data? (Y/N):")
        if reply[0].upper() == "Y" or reply[0].upper() == "N": break
    if reply[0].upper() == "N":
        enterData = False