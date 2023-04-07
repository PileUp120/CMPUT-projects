import ast
def unzip (inList):
    list_1 = []
    list_2 = []
    for e in inList:
        list_1.append(e[0])
        list_2.append(e[1])
    return (list_1,list_2)
def main():
    toUnzip = input("Enter a list of 2-value tuples:")
    print(unzip(ast.literal_eval(toUnzip)))
main()