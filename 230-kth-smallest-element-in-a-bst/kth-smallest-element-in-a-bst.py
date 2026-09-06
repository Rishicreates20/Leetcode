# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def kthSmallest(self, root, k):
        stack = []
        curr = root
        
        while curr or stack:
            # Reach the left-most node of the current node
            while curr:
                stack.append(curr)
                curr = curr.left
            
            # Pop the current smallest node
            curr = stack.pop()
            
            # Decrement k and check if this is the target
            k -= 1
            if k == 0:
                return curr.val
            
            # Move to the right subtree
            curr = curr.right
            
        return -1