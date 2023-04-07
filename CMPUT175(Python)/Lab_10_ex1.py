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


def preorder(tree):
  if tree != None:
    print(tree.getRootVal(), end=' ')
    preorder(tree.getLeft())
    preorder(tree.getRight())


def inorder(tree):
  if tree != None:
    inorder(tree.getLeft())
    print(tree.getRootVal(), end=' ')
    inorder(tree.getRight())


def postorder(tree):
  if tree != None:
    postorder(tree.getLeft())
    postorder(tree.getRight())
    print(tree.getRootVal(), end=' ')


def findMinValue(tree):
  minValue = None
  if minValue == None and tree!= None:
    minValue = tree.getRootVal()
  elif minValue != None and tree.getRootVal() < minValue:
    minValue = tree.getRootVal()
  if tree != None:
    left = findMinValue(tree.getLeft())
    right = findMinValue(tree.getRight())
    if left != None and left < minValue:
      minValue = left
    if right != None and right < minValue:
      minValue = right    
  return minValue


def findMaxValue(tree):
  maxValue = None
  if maxValue == None and tree!= None:
    maxValue = tree.getRootVal()
  elif maxValue != None and tree.getRootVal() > maxValue:
    maxValue = tree.getRootVal()
  if tree != None:
    left = findMaxValue(tree.getLeft())
    right = findMaxValue(tree.getRight())
    if left != None and left > maxValue:
      maxValue = left
    if right != None and right > maxValue:
      maxValue = right    
  return maxValue


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

  preorder(tree)
  print()
  inorder(tree)
  print()
  postorder(tree)
  print()

  print('Max value in tree:', findMaxValue(tree))
  print('Min value in tree:', findMinValue(tree))

if __name__ == "__main__":
  main()