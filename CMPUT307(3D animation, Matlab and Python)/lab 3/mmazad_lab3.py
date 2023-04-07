from cmath import cos, sin
import numpy as np
#########################
#       Exercise 1      #
#########################

def generateTranslationMatrix(x, y, z):
    '''
    return the homogeneous transformation matrix for the given translation (x, y, z)
      parameter: 
        sx, sy, sz: scaling parameters for x-, y-, z-axis, respectively
      return:
        ndarray of size (4, 4)
    '''
    t_matrix = np.identity(4)
    t_matrix[0,3] = x
    t_matrix[1,3] = y
    t_matrix[2,3] = z
    return t_matrix

def generateScalingMatrix(sx, sy, sz):
    '''
    return the homogeneous transformation matrix for the given scaling parameters (sx, sy, sz)
      parameter:
        sx, sy, sz: scaling parameters for x-, y-, z-axis, respectively
      return:
        ndarray of size (4, 4)
    '''
    s_matrix = np.identity(4)
    s_matrix[0,0] = sx
    s_matrix[1,1] = sy
    s_matrix[2,2] = sz
    pass

def generateRotationMatrix(rad, axis):
    '''
    return the homogeneous transformation matrix for the given rotation parameters (rad, axis)
      parameter:
        rad: radians for rotation
        axis: axis for rotation, can only be one of ('x', 'y', 'z', 'X', 'Y', 'Z')
      return: 
        ndarray of size (4, 4)
    '''
    assert((axis.lower() == 'x') or (axis.lower() == 'y') or (axis.lower() == 'z'))
    
    r_matrix = np.identity(4)
    cos_rad = np.cos(rad)
    sin_rad = np.sin(rad)
    param_list = [cos_rad, sin_rad, -sin_rad, cos_rad]
    fixed_axis = -1
    
    if (axis.lower() == 'x'):
      fixed_axis = 0
    elif(axis.lower() == 'y'):
      fixed_axis = 1
    elif(axis.lower() == 'z'):
      fixed_axis = 2
    
    for i in range(3):
      for j in range(3):
        if((i != fixed_axis) and (j != fixed_axis)):
          r_matrix[i, j] = param_list.pop()

    if (axis.lower() == 'y'):
      r_matrix[0, 2] *= -1
      r_matrix[2, 1] *= -1
    
    return r_matrix

# Case 1
def part1Case1():
    # translation matrix
    t = generateTranslationMatrix(2,3,-2)
    # scaling matrix
    s = generateScalingMatrix(0.5,2,2)
    # rotation matrix
    r = generateRotationMatrix(np.deg2rad(45), 'z')
    # data in homogeneous coordinate
    data = np.array([2, 3, 4, 1]).T
    print("After t: ")
    print(t*data)
    print("After s: ")
    print((t*s)*data)
    print("After r: ")
    print(((t*s)*r)*data)

# Case 2
def part1Case2():
    # translation matrix
    t = generateTranslationMatrix(3,1,3)
    # scaling matrix
    s = generateScalingMatrix(4,-2,3)
    # rotation matrix
    r = generateRotationMatrix(np.deg2rad(-30), 'y')
    # data in homogeneous coordinate
    data = np.array([6, 5, 2, 1]).T
    print("After s: ")
    print(s*data)
    print("After t: ")
    print((s*t)*data)
    print("After r: ")
    print(((s*t)*r)*data)

# Case 3
def part1Case3():
    # translation matrix
    t = generateTranslationMatrix(5,2,-3)
    # scaling matrix
    s = generateScalingMatrix(2,2,-2)
    # rotation matrix
    r = generateRotationMatrix(np.deg2rad(15), 'x')
    # data in homogeneous coordinate
    data = np.array([3, 2, 5, 1]).T
    print("After r: ")
    print(r*data)
    print("After r: ")
    print((r*s)*data)
    print("After t: ")
    print(((r*s)*t)*data)

#########################
#       Exercise 2      #
#########################

# Part 1
def generateRandomSphere(r, n):
    '''
    generate a point cloud of n points in spherical coordinates (radial distance, polar angle, azimuthal angle)
      parameter:
        r: radius of the sphere
        n: total number of points
    return:
      spherical coordinates, ndarray of size (3, n), where the 3 rows are ordered as (radial distances, polar angles, azimuthal angles)
    '''
    spherical_list = np.random.rand(3,n)
    
    for i in range(3):
      for j in range(n):
        if (i == 0):
          spherical_list[i,j]*=r
        elif ((i == 1) or (i == 2)):
          spherical_list[i,j]*=(2*np.pi)
    
    return spherical_list

def sphericalToCatesian(coors):
    '''
    convert n points in spherical coordinates to cartesian coordinates, then add a row of 1s to them to convert
    them to homogeneous coordinates
      parameter:
        coors: ndarray of size (3, n), where the 3 rows are ordered as (radial distances, polar angles, azimuthal angles)
    return:
      catesian coordinates, ndarray of size (4, n), where the 4 rows are ordered as (x, y, z, 1)
    '''
    assert(np.shape(coors)[0] == 3)
    cartesian_list = np.ones((4,np.shape(coors)[1]))
    
    for j in range(np.shape(coors)[1]):
      cartesian_list[0,j] = coors[0,j]*np.cos(coors[2,j])*np.sin(coors[1,j])
      cartesian_list[1,j] = coors[0,j]*np.sin(coors[2,j])*np.sin(coors[1,j])
      cartesian_list[2,j] = coors[0,j]*np.cos(coors[1,j])
    
    return cartesian_list

# Part 2
def applyRandomTransformation(sphere1):
    '''
    generate two random transformations, one of each (scaling, rotation),
    apply them to the input sphere in random order, then apply a random translation,
    then return the transformed coordinates of the sphere, the composite transformation matrix,
    and the three random transformation matrices you generated
      parameter:
        sphere1: homogeneous coordinates of sphere1, ndarray of size (4, n), 
                 where the 4 rows are ordered as (x, y, z, 1)
      return:
        a tuple (p, m, t, s, r)
        p: transformed homogeneous coordinates, ndarray of size (4, n), 
                 where the 4 rows are ordered as (x, y, z, 1)
        m: composite transformation matrix, ndarray of size (4, 4)
        t: translation matrix, ndarray of size (4, 4)
        s: scaling matrix, ndarray of size (4, 4)
        r: rotation matrix, ndarray of size (4, 4)
    '''
    assert(np.shape(sphere1)[0] == 4)
    axes = ['x', 'y', 'z']
    s = generateScalingMatrix(np.random.uniform(1,5), np.random.uniform(1,5), np.random.uniform(1,5))
    r = generateRotationMatrix(np.deg2rad(np.random.randint(0,90)), axes[np.random.randint(0,3)])
    t = generateTranslationMatrix(np.random.uniform(1,5), np.random.uniform(1,5), np.random.uniform(1,5))
    t_order = np.random.randint(0,3)
    if(t_order == 0):
      m = (r*s)*t
    elif(t_order == 1):
      m = (r*t)*s
    elif(t_order == 2):
      m = (s*t)*r
    p = m*sphere1
    return((p,m,t,s,r))

def calculateTransformation(sphere1, sphere2):
    '''
    calculate the composite transformation matrix from sphere1 to sphere2
      parameter:
        sphere1: homogeneous coordinates of sphere1, ndarray of size (4, n), 
                 where the 4 rows are ordered as (x, y, z, 1)
        sphere2: homogeneous coordinates of sphere2, ndarray of size (4, n), 
                 where the 4 rows are ordered as (x, y, z, 1)
    return:
      composite transformation matrix, ndarray of size (4, 4)
    '''
    # let sphere2 = transform * sphere1
    # multiply both sides by inverse of sphere1
    # sphere2 * sphere1^-1 = transform * sphere1 * sphere1^-1
    # sphere2 * sphere1^-1 = transform
    t_matrix = sphere2 * np.linalg.pinv(sphere1) #np.linalg.pinv uses svd, hence it skips the need for us to use svd
    return t_matrix

def decomposeTransformation(m):
    '''
    decomposite the transformation and return the translation, scaling, and rotation matrices
      parameter:
        m: homogeneous transformation matrix, ndarray of size (4, 4)

    return:
      tuple of three matrices, (t, s, r)
        t: translation matrix, ndarray of size (4, 4)
        s: scaling matrix, ndarray of size (4, 4)
        r: rotation matrix, ndarray of size (4, 4)
    '''
    
    t = np.identity(4)
    s = np.identity(4)
    r = np.identity(4)
    # from any transformation matrix, we can obtain the translation matrix by looking at the last column only, and setting the rest to be the identity
    t[0,3] = m[0,3]
    t[1,3] = m[1,3]
    t[2,3] = m[2,3]

    #to figure out what is the axis of rotation, we check if first row, second column in non zero, if so then it is z-axis rotation
    #if it is zero, we check if second row, third column is non-zero, if it is then it is x-axis rotation
    #if both are zero, then it is y-axis rotation
    rot_axix = ''
    if (m[0,1] == 0):
      if (m[1,2] == 0):
        rot_axix = 'y'
      else:
        rot_axix = 'x'
    else:
      rot_axix = 'z'

    sx = 0
    sy = 0
    sz = 0
    cos_t = 0
    sin_t = 0

    if(rot_axix == 'z'):
      sz = m[2, 2]
      
      if( ((m[0,0] / m[1,1]) * m[0,1]) == (-1 * m[1,0])):
        sin_t = np.sin(np.arctan((m[1,0] / m[0,0])))
        cos_t = np.cos(np.arctan((m[1,0] / m[0,0])))
      else:
        sin_t = np.sin(np.arctan(((-1 * m[0,1]) / m[0,0])))
        cos_t = np.cos(np.arctan(((-1 * m[0,1]) / m[0,0])))
      
      sx = m[0,0] / cos_t
      sy = m[1,1] / cos_t
      r[0,0] = r[1,1] = cos_t
      r[1,0] = sin_t
      r[0,1] = -1*sin_t

    elif(rot_axix == 'x'):
      sx = m[0, 0]

      if( ((m[1,1] / m[2,2]) * m[1,2]) == (-1 * m[2,1])):
        sin_t = np.sin(np.arctan((m[2,1] / m[1,1])))
        cos_t = np.cos(np.arctan((m[2,1] / m[1,1])))
      else:
        sin_t = np.sin(np.arctan(((-1 * m[1,2]) / m[1,1])))
        cos_t = np.cos(np.arctan(((-1 * m[1,2]) / m[1,1])))

      sy = m[1,1] / cos_t
      sz = m[2,2] / cos_t
      r[1,1] = r[2,2] = cos_t
      r[2,1] = sin_t
      r[1,2] = -1*sin_t
    elif(rot_axix == 'y'):
      sy = m[1, 1]

      if( ((m[0,0] / m[2,2]) * m[0,2]) == (-1 * m[2,0])):
        sin_t = np.sin(np.arctan((m[0,2] / m[2,2])))
        cos_t = np.cos(np.arctan((m[0,2] / m[2,2])))
      else:
        sin_t = np.sin(np.arctan((m[0,2] / m[0,0])))
        cos_t = np.cos(np.arctan((m[0,2] / m[0,0])))

      sx = m[0,0] / cos_t
      sz = m[2,2] / cos_t
      r[0,0] = r[2,2] = cos_t
      r[0,2] = sin_t
      r[2,0] = -1*sin_t
    
    s[0,0] = sx
    s[1,1] = sy
    s[2,2] = sz

    return ((t, s, r))


#########################
#      Main function    #
#########################
def main():
  part1Case1()
  part1Case2()
  part1Case3()

  print("Part 2:")
  test_sphere = sphericalToCatesian(generateRandomSphere(4, 25)) #create a random sphere or radius 4 with 25 sampled points 
  transformed_sphere_info = applyRandomTransformation(test_sphere) #gets a tuple with elemets transformed sphere, transformation matrix, translation, scaling, rotation
  decomposed_transformations = decomposeTransformation(transformed_sphere_info[1])

  print(np.allclose( calculateTransformation(test_sphere, transformed_sphere_info[0]), transformed_sphere_info[1]))
  print(np.allclose(transformed_sphere_info[2], decomposed_transformations[0]))
  print(np.allclose(transformed_sphere_info[3], decomposed_transformations[1]))
  print(np.allclose(transformed_sphere_info[4], decomposed_transformations[2]))


if __name__ == "__main__":
    main()