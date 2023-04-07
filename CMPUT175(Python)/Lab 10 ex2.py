class BinaryTree:
    def __init__(self, rootElement):
        self.key = rootElement
        self.left = None
        self.right = None

    def getLeft(self):
        return self.left

    def getRight(self):
        return self.right

    def getRootVal(self):
        return self.key

    def setRootVal(self,val):
        self.key=val

    def insertLeft(self,newNode):
        if self.left == None:
            self.left = BinaryTree(newNode)
        else:
            t = BinaryTree(newNode)
            t.left = self.left
            self.left = t

    def insertRight(self,newNode):
        if self.right == None:
            self.right = BinaryTree(newNode)
        else:
            t = BinaryTree(newNode)
            t.right = self.right
            self.right = t
    
def contains(tree,anObject):
    found = False
    if tree != None and not found:
        if tree.getRootVal() == anObject:
            found = True
    if tree != None:
        left = contains(tree.getLeft(),anObject)
        right = contains(tree.getRight(),anObject)
        if left:
            found = True
        elif right:
            found = True
    return found
            
    
def add(tree,anObject):
    if tree == None:
        tree.setRootVal(anObject)
    elif tree.getRight() == None:
        tree.insertRight(anObject)
    else:
        while tree.getLeft() != None:
            tree = tree.getLeft()
    tree.insertLeft(anObject)
        
    
def delete(tree,anObject):
    if contains(tree,anObject):
        current = tree
        while current.getRootVal() != anObject:
            
    else:
        raise Exception("Tree does not contain %s" % anObject)

def main():
    tree = BinaryTree(1)
    tree.insertLeft(2)
    tree.insertRight(7)
    tree.getLeft().insertLeft(3)
    tree.getLeft().insertRight(6)
    tree.getLeft().getLeft().insertLeft(4)
    tree.getLeft().getLeft().insertRight(5)
    tree.getRight().insertLeft(8)
    tree.getRight().insertRight(9)
    
    print(contains(tree,7))
    
    add(tree,24)
    
    print(contains(tree,24))

if __name__ == "__main__":
    main()