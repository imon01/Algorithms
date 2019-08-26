from string import ascii_uppercase as A

"""
KSum implementaiont and Kadane's Algorithm for max subarray.

KSum remarks: Translation from
https://www.sigmainfy.com/blog/k-sum-problem-analysis-recursive-implementation-lower-bound.html
"""

def firstDuplicate(a):

	"""
	:type a: list[int]
	:rtype n: char
	"""	

	index = 0
	m = {}
	for num in a  :

		#store (key, index) pairs if new
		if num not in m:
			m.setdefault(num, [index])
		#number exist already and first occurance exist
		else:
			m[num].append(index)
		index = index + 1

	key_set = list( m.keys() )

	# trim table and 
	for key in key_set:
		#if unique occurance, remove... not significant
		if len(m[key]) < 2:
			m.pop(key, None)
		#duplicate, remove first  index
		else:
			m[key].pop(0)

	min = len(a) + 1
	n  = 0
	for key in m:
		if m[key][0] < min:
			min = m[key][0]
			n = key
	if min == ( len(a) + 1):
		m = -1

	return n

def firstNonRepeatChar(s):
	"""
	first non-repeating character
	"""
	if len(s) < 2:
		return
	sum = 0
	ascii_set = []
	c = None

	for char in s:
		c = ord(char)
		sum = sum + c
	
		if c not in ascii_set:
			ascii_set.append(c)

	for num in ascii_set:
		n = sum % num
		k = (sum - num) / n
		check_sum = sum
		c = chr( check_sum)
		print("n: " + str(n) + " k: "+str(k) + "  check_sum: " + str(check_sum))
		print("     charachter: "  + c)

	
def twoSum(l, target):
    """
    :type nums: List[int]
	:type target: int
    :rtype: List[List[int]]        
    """

	table = {}
	for i in l:
		table.setdefault( (target -i), i)
	result = [] 
	for key in table:
		if key in l:
			result.append( [table[key],key]	)
	return result 

def threeSum( list_t, target):
    """
    :type nums: List[int]
	:type target: int
    :rtype: List[List[int]]        
    """
	table = {}
	result = [] 
	for i in list_t:
		table.setdefault(target-i, i)

	key_val = 0
	for val in table:
		for num in list_t:
			key_val = val - num 
			if key_val in list_t:
				tuple4=[key_val, num, table[val] ] 
				tuple4.sort()
				if tuple4 not in result:	
					result.append(tuple4)
	for quadruple in result:
		print(quadruple)


def threeSum(nums, target):
    """
    :type nums: List[int]
	:type target: int
    :rtype: List[List[int]]        
    """
            
    nums.sort()                                
    
    result = []                    
    i,j = 0,0
    N= len(nums) 
    for i in range(N):
        if i > 0 and nums[i] == nums[i-1]:
            continue            
        l, r = i+1, N-1
        target = nums[i]*-1
        while( l < r):
            if target == nums[l]+nums[r]:                    
                result.append( [nums[i], nums[l], nums[r]])
                l += 1                    
                while l < r and nums[l] == nums[l - 1]: l += 1                    
            elif nums[l] + nums[r] < target:
                l+=1
            else:
                r -=1
                
    return result	


def KSum(nums, k, target, start):
    """
    :type nums: List[int]
	:type target: int
	:type start: int
    :rtype: List[List[int]]        
    """
	results = []
	if k == 2:
		i = start 
		j = len(nums) -1
		while i < j:
			if i > start and nums[i] == nums[i-1]:
				i+=1
				continue
			if (nums[i] + nums[j]) == target:
				t = [ nums[i], nums[j]]
				i+=1; j-=1
				results.append(t)
			elif (nums[i]+nums[j] ) > target:
				j-=1
			else:
				i+=1

		return results
	for i in range(start, len(nums)):
		#if i > start and nums[i] == nums[i-1]:
		#	continue
		k_sum_list  = KSum(nums, k-1, target - nums[i], i+1)		
		for tuple_n in k_sum_list:
			t = [nums[i]]
			t +=tuple_n
			t.sort()
			if t not in results:	
				results.append(t)

	return results 
			 	
def maxSubArray(A):
	"""
	"Kadane's algorithm
	"
	" list A
	"""
	max_temp, max_global = A[0], A[0]
	start, end, n = 0,1,0

	for i in range(1, len(A)):
		n = A[i]
		max_temp = max(n, max_temp + n)

		if max_temp == n:
			start = i
		max_global = max( max_global, max_temp)
	
		if max_global == max_temp:
			end = i	

	if end < start:
		start = A.index(max_global)
		end = start
	print("Subarray max: "+ str(max_global)+",   <start,end>=< "+str(start)+", "+str(end) +">")


def test():
	k = [1,1,2,1,2,3,4,5,6,7]
	k2 = [1,0,-1,0,-2,2]
	k2.sort()
	l = KSum(k, 4, 10, 0)
	l2 = KSum(k2, 4, 0, 0)
	for item in l2:
		print(item)

if __name__ == "__main__":
	test()
