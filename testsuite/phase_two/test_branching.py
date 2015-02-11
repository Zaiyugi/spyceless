# Test Branching

def foo():
   x = 50
   y = 30
   z = 10

   __debug__

   if x == 50:
      if y == 30:
         if z == y / 2:
            println z
         else:
            println str(z) + " is y / 3"
         end
      end
   end

end

foo()
