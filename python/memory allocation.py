class MemoryBlock:
    def __init__(self,size):
     self.size =size
     self.is_allocated = False
     
    def __repr__(self):
       return f"Size:{self.size},Allocated: {self.isallocated}"
    
class MemoryAllocator:
   def __init__(self,memory_blocks):
      self.memory_blocks =[MemoryBlock(size) for size in memory_blocks]
      self.last_allocated_index =0 

   def first_fit(self,process_size):
      for block in self.memory_blocks:
         if not block.is_allocated and block.size >= process_size:
            block.is_allocated =True
            print(f"process of size {process_size} allocated to block of size {block.size}")
            return True 
      print (f"process of size {process_size}could not be allocated. ")
      return False
   def best_fit(self,process_size):
      best_block = None
      for block in self.memory_blocks:
         if not block.is_allocated and block.size>=process_size:
            if best_block is None or block.size < best_block.size:
               best_block= block
      
      if best_block:
         best_block.is_allocated = True
         print(f"Process of size {process_size} is allocated to block of size {best_block.size}")
         return True
      else:
         print(f"Process of size {process_size} could not be allocated")
         return False
   def  next_Fit(self,process_size):
      n = len(self.memory_blocks)
      for i in range(n):
         index = (self.last_allocated_index + i)%n
         block = self.memory_blocks[index]
         if not block.is_allocated and block.size >= process_size:
            block.is_allocated = True
            self.last_allocated_index = index
            print(f"process of size {process_size} allocated to block of size {block.size}")
            return True
      print(f"process of size {process_size} could not be allocated")
      return False
   def worst_fit(self,process_size):
      worst_block = None
      for block in self.memory_blocks:
         if not block.is_allocated and block.size>= process_size:
            if worst_block is None or block.size> worst_block.size:
               worst_block = block
      
      if worst_block:
         worst_block.is_allocated = True
         print(f"process of size {process_size} allocated to block of size{worst_block.size}")
         return True
      print(f"Process of size {process_size} could not be allocated. ")
      return False
   
   def reset(self):
      for block in self.memory_blocks:
         block.is_allocated = False
      self.last_allocated_index = 0
      print("memory reset. all blocks are now free.\n")

memory_sizes = [100,500,200,300,600]
allocator = MemoryAllocator(memory_sizes)

process_sizes = [ 212 , 417, 112, 426]


print ("\n first fit allocation: ")
allocator.reset()
for size in process_sizes:
   allocator.first_fit(size)

print("\n best fit allocation: ")
allocator.reset()
for size in process_sizes:
   allocator.best_fit(size)

print("\n next fit allocation: ")
allocator.reset()
for size in process_sizes:
   allocator.next_Fit(size)

print("\n worst fit allocation: ")
allocator.reset()
for size in process_sizes:
   allocator.worst_fit(size)


  
        
