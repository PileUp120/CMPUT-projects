def readAccounts(infile):
    content = infile.read()
    line_list = content.splitlines()
    accts_dict = {}
    for i in line_list:
        line_list[line_list.index(i)] = i.split(sep = ';')
    for e in line_list:
        try:
            float(e[1])
            accts_dict[e[0]] = float(e[1])
        except ValueError:
            print("ValueError. Account for", e[0]," not added: illegal value for balance")
    return accts_dict
def processAccounts(account):
    userName = input("Enter account name, or 'Stop' to exit:")
    while userName.capitalize() != 'Stop':
        try:
            acctName = account[userName]
            questionString = "Enter transaction amount for " + str(userName) +":"
            valAdd = input(questionString)
            try:
                if account[userName] >=0:
                    added = account[userName] + float(valAdd)
                    account[userName] = added
                    print("New balance for account ",userName,":",account[userName])
                    userName = input("Enter account name, or 'Stop' to exit:")
                else:
                    print("Minimum balance reached")
                    userName = input("Enter account name, or 'Stop' to exit:")
            except ValueError:
                print("Value Error. Incorrect Amount. Transaction cancelled.")
                userName = input("Enter account name, or 'Stop' to exit:")            
        except KeyError:
            print("KeyError. Account for", userName," does not Exist. Transaction cancelled.")
            userName = input("Enter account name, or 'Stop' to exit:")
            
fileName = input("Enter filename>")
try:
    infile = open(fileName,'r')
except IOError:
    print("IOError. %s does not exist" %(fileName))
else:
    processFile = readAccounts(infile)
    infile.close()
    processAccounts(processFile)

    