def decryptCode(name):
    codeFile = open(name,'r')
    codeContent = codeFile.read()
    codeFile.close()
    fileLines = codeContent.splitlines()
    for line in fileLines:
        replacer = line.strip()
        fileLines[fileLines.index(line)] = replacer
    for item in fileLines:
        keyCodesp = item.split(' ')
        fileLines[fileLines.index(item)] = keyCodesp
    for element in fileLines:
        if len(element)<2:
            if len(element) == 0:
                print("Missing Key and Missing Text!")
            elif element[0].isnumeric():
                print("Missing Text!")
            else:
                print("Missing Key!")
        else:
            for item in element:
                key = int(element[0])
                decrypted=''
                for letter in element[1]:
                    order = ord(letter)
                    order -= key
                    if letter.isupper():
                        if order > ord('Z'):
                            order -= 26
                        elif order < ord('A'):
                            order += 26
                    elif letter.islower():
                        if order > ord('z'):
                            order -= 26
                        elif order < ord('a'):
                            order += 26
                    decrypted += chr(order)
            print(decrypted)            

FileName = input("Enter the input filename:")
decryptCode(FileName)